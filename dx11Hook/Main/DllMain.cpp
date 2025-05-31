#include <Windows.h>
#include "../Hook/Hook.h"

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    Hook::Initialize();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        Hook::Shutdown();
    }
    return TRUE;
}
