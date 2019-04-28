#include <memory>

#include "Global.h"
#include "WindowsApplication.h"

using namespace Platform;
using namespace Engine;

void WindowsApplication::Initialize()
{
    CreateMainWindow();
    m_hDc = GetDC(m_hWnd);
    gpGlobal->GetConfiguration().hWnd = (void*)m_hWnd;

    BaseApplication::Initialize();

    m_pWindowsInputManager = std::dynamic_pointer_cast<WindowsInput>(m_pInputManager);
    if (m_pWindowsInputManager)
        m_pWindowsInputManager->Initialize();
}

void WindowsApplication::Shutdown()
{
    if (m_pWindowsInputManager)
        m_pWindowsInputManager->Shutdown();

    BaseApplication::Shutdown();
}

void WindowsApplication::Tick()
{
    if (m_pWindowsInputManager)
        m_pWindowsInputManager->Tick();

    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }

    BaseApplication::Tick();

}

void WindowsApplication::CreateMainWindow()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "GameEngineApplication";

    RegisterClassEx(&wc);

    int height_adjust = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
    int width_adjust = (GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER));

    m_hWnd = CreateWindowEx(0,
                            "GameEngineApplication",
                            gpGlobal->GetConfiguration().appName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            gpGlobal->GetConfiguration().width + width_adjust,
                            gpGlobal->GetConfiguration().height + height_adjust,
                            NULL,
                            NULL,
                            hInstance,
                            this);

    ShowWindow(m_hWnd, SW_SHOW);
}

LRESULT CALLBACK WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsInput::PeekWindowsInputMessage(message, wParam, lParam);

    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            m_bQuit = true;
        } 
    }

    return DefWindowProc (hWnd, message, wParam, lParam); 
}