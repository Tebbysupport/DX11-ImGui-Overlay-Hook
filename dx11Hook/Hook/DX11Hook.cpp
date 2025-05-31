#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>
#include "DX11Hook.h"
#include "../UI/Menu.h"
#include "../External/ImGui/imgui_impl_dx11.h"
#include "../External/ImGui/imgui_impl_win32.h"
#include "../Utils/Utils.h"
#include "../Utils/skcrypt.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_Context = nullptr;
IDXGISwapChain* g_SwapChain = nullptr;
ID3D11RenderTargetView* g_RenderTargetView = nullptr;
bool                    g_Initialized = false;

typedef HRESULT(__stdcall* Present_t)(IDXGISwapChain*, UINT, UINT);
Present_t oPresent = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static bool showMenu = true;
static WNDPROC oWndProc = nullptr;

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

void CreateRenderTarget()
{
    if (g_RenderTargetView)
    {
        g_RenderTargetView->Release();
        g_RenderTargetView = nullptr;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    if (FAILED(g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer)))
        return;

    if (FAILED(g_Device->CreateRenderTargetView(pBackBuffer, nullptr, &g_RenderTargetView)))
    {
        pBackBuffer->Release();
        return;
    }

    pBackBuffer->Release();
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!g_Initialized)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_Device)))
        {
            g_Device->GetImmediateContext(&g_Context);
            g_SwapChain = pSwapChain;

            DXGI_SWAP_CHAIN_DESC desc;
            pSwapChain->GetDesc(&desc);
            HWND hWnd = desc.OutputWindow;

            static bool wndHooked = false;
            if (!wndHooked)
            {
                oWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProcHook);
                wndHooked = true;
            }

            //if (!hWnd || !IsWindow(hWnd))
            //{
            //    MessageBoxA(0, "Fenêtre invalide (HWND) !", "Erreur", MB_ICONERROR);
            //    return oPresent(pSwapChain, SyncInterval, Flags);
            //}

            ImGui::CreateContext();
            Menu::Init();
            ImGui_ImplWin32_Init(hWnd);
            ImGui_ImplDX11_Init(g_Device, g_Context);

            g_Initialized = true;

            //MessageBoxA(0, "Hook Present actif !", "DX11Hook", MB_OK);
        }
    }

    if (!g_RenderTargetView)
        CreateRenderTarget();

    g_Context->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

    if (IsKeyPressed(VK_F2))  
    {
        showMenu = !showMenu;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (showMenu)
    {
        Menu::Render();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

namespace DX11Hook
{
    void Init()
    {
        DXGI_SWAP_CHAIN_DESC scDesc = {};
        scDesc.BufferCount = 1;
        scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scDesc.OutputWindow = GetForegroundWindow();
        scDesc.SampleDesc.Count = 1;
        scDesc.Windowed = TRUE;
        scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        ID3D11Device* pDevice = nullptr;
        ID3D11DeviceContext* pContext = nullptr;
        IDXGISwapChain* pSwapChain = nullptr;

        if (FAILED(D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            &featureLevel,
            1,
            D3D11_SDK_VERSION,
            &scDesc,
            &pSwapChain,
            &pDevice,
            nullptr,
            &pContext)))
        {
            MessageBoxA(0, skCrypt("Dummy swapchain creation failed").decrypt(), "DX11Hook", MB_ICONERROR);
            return;
        }

        void** vTable = *reinterpret_cast<void***>(pSwapChain);
        oPresent = reinterpret_cast<Present_t>(vTable[8]);

        DWORD oldProtect;
        VirtualProtect(&vTable[8], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
        vTable[8] = reinterpret_cast<void*>(&hkPresent);
        VirtualProtect(&vTable[8], sizeof(void*), oldProtect, &oldProtect);

        pSwapChain->Release();
        pContext->Release();
        pDevice->Release();
    }

    void Shutdown()
    {
        if (g_Initialized)
        {
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            if (g_RenderTargetView)
            {
                g_RenderTargetView->Release();
                g_RenderTargetView = nullptr;
            }

            g_Initialized = false;
        }
    }
}
