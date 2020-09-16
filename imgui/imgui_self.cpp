#include "imgui_self.h"

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};


bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int imGui(int, char**)
{

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("amonug"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("amongus"), WS_OVERLAPPEDWINDOW, 100, 100, 500, 300, NULL, NULL, wc.hInstance, NULL);


    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;



    ImGui::StyleColorsDark();


    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);


	bool show_game_settings = false;
    bool show_text_input = false;
	bool console = false;
	int maximpostors = 2;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	char buf[2048] = { 0 };
	char buf2[2048] = { 0 };
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }


        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
        

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("config");                                                  
                
            ImGui::Checkbox("Custom Text Input", &show_text_input);
			ImGui::SameLine();
			ImGui::Checkbox("Custom Settings", &show_game_settings);
			
            if (ImGui::Button("ToggleCheat"))                            
                cheat = !cheat;
			ImGui::SameLine();
			ImGui::Text("ToggleCheat = %d", cheat);

            if (ImGui::Button("ToggleHook"))
                hookPressed = !hookPressed;
            ImGui::SameLine();
            ImGui::Text("ToggleHook = %d", hook);

			if (ImGui::Button("ToggleImpostorMode"))
				impostorMode = !impostorMode;
			ImGui::SameLine();
			ImGui::Text("ToggleImpostor = %d", impostorMode);

			if (ImGui::Button("TeleportAll"))
				TeleportAll = true;

			if (ImGui::Button("console")) {
				(console ? NewConsole() : CloseConsole());
				console = !console;
			}
				
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
		
        if (show_text_input) {
            
            ImGui::Begin("Text Input");
            ImGui::InputTextMultiline("for chat", buf, IM_ARRAYSIZE(buf), ImVec2(0, 0), ImGuiInputTextFlags_None);
            strcpy_s(customText, buf);

			ImGui::InputTextMultiline("for name", buf2, IM_ARRAYSIZE(buf), ImVec2(0, 0), ImGuiInputTextFlags_None);
			ImGui::SameLine();
			if(ImGui::Button("set"))
				strcpy_s(customName, buf2);
			
                
            if (ImGui::Button("close"))
                show_text_input = !show_text_input;
            ImGui::End();
        }

		if (show_game_settings && cheat) {
			GameOptionsData__Fields& gameOptionsPlayer = getGameOptionFields();
			GameOptionsData__StaticFields*& gameOptionsGlobal = getGameOptionStaticFields();

			ImGui::Begin("game settings");
			ImGui::SliderFloat("PlayerSpeedMod", &gameOptionsPlayer.PlayerSpeedMod, 0.0f, 30.0f, "%.1f", 1.0f);
			ImGui::SliderFloat("ImpostorLightMod", &gameOptionsPlayer.ImpostorLightMod, 0.0f, 500.0f, "%.1f", 1.0f);
			ImGui::SliderFloat("CrewLightMod", &gameOptionsPlayer.CrewLightMod, 0.0f, 500.0f, "%.1f", 1.0f);
			ImGui::SliderInt("NumImpostors", &gameOptionsPlayer.NumImpostors, 0, 30);
			ImGui::SliderInt("MaxImpostors", &maximpostors, 0, 30);
			for (int i = 0; i < gameOptionsGlobal->MaxImpostors->max_length; i++) {
				gameOptionsGlobal->MaxImpostors->vector[i] = maximpostors;
				
			}
			for (int i = 0; i < gameOptionsGlobal->RecommendedImpostors->max_length; i++) {
				gameOptionsGlobal->RecommendedImpostors->vector[i] = maximpostors;
			
			}
			ImGui::End();
		
		}

        mainLoop();
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
	hooks::end();
    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
    
    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}