#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

DWORD findProcessID()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    do {
        if (!wcscmp(pe32.szExeFile, L"notepad.exe")) {
            return pe32.th32ProcessID;
        }

    } while (Process32Next(hProcessSnap, &pe32));
    return 0;
}

int main()
{
    DWORD pid;
    HANDLE hProcess;
    LPVOID lpBaseAddress;
    const char* dllName = "Dll_test.dll";
    size_t sz = strlen(dllName);
    pid = findProcessID();
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
    lpBaseAddress = VirtualAllocEx(hProcess, NULL, sz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, lpBaseAddress, dllName, sz, NULL);
    HMODULE hModule = GetModuleHandle(L"kernel32.dll");
    LPVOID lpStartAddress = GetProcAddress(hModule, "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpStartAddress, lpBaseAddress, 0, NULL);
    if (hThread)
    {
        printf("Injection successful!\n");
    }
    else
    {
        printf("Injection unsuccessful!\n");
    }
}
