#pragma once
#include "..\imgui\imgui.h"
#include "..\imgui\examples\imgui_impl_win32.h"
#include "..\imgui\examples\imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#pragma comment(lib, "d3d11.lib")
int imGui();