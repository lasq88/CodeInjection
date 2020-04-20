#include "pch.h"
#include <Windows.h>
#include <psapi.h>
#include <winuser.h>

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
    IN DWORD     nReason,
    IN LPVOID    Reserved)
{
    BOOLEAN bSuccess = TRUE;



    switch (nReason)
    {
    case DLL_PROCESS_ATTACH:

        wchar_t wnameProc[MAX_PATH];
        if (GetProcessImageFileNameW(GetCurrentProcess(), wnameProc, sizeof(wnameProc) / sizeof(*wnameProc)) == 0) {
            bSuccess = FALSE;
        }
        else
        {
            MessageBoxW(NULL, wnameProc, L"Process name", MB_ICONINFORMATION);
            bSuccess = TRUE;
        }

        break;

    case DLL_PROCESS_DETACH:

        break;
    }
    return bSuccess;
}
