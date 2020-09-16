#pragma once
#include "..\imgui\imgui.h"
#include "..\imgui\examples\imgui_impl_win32.h"
#include "..\imgui\examples\imgui_impl_dx9.h"
#include "..\framework\il2cpp-appdata.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "..\mainLoop.h"
#include "..\global.h"
#include "..\hooks.h"
#pragma comment(lib, "d3d9.lib")
int imGui(int, char**);