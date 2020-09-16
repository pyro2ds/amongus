

#define WIN32_LEAN_AND_MEAN

#include "..\features.h"
#include "..\imgui\imgui_self.h"

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

void Run(HMODULE hModule)
{

    imGui(0, 0);
    
    CloseConsole();
    FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}