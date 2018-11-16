#include <memory>

#include "Event.h"
#include "EventManager.h"
#include "WindowsApplication.h"

using namespace Engine;
using namespace Platform;

namespace Engine
{
    WindowsApplication g_App;
    std::unique_ptr<IApplication> g_pApp = std::make_unique<WindowsApplication>(g_App);
}

void WindowsApplication::Initialize()
{
    CreateMainWindow();
    m_hDc = GetDC(m_hWnd);

    BaseApplication::Initialize();

    DECLARE_EVENT(eEv_System_AppLog, AppInitEv, std::string("WindowsApplication initialize"));
    EMITTER_EVENT(AppInitEv);
}

void WindowsApplication::Shutdown()
{
    BaseApplication::Shutdown();
}

void WindowsApplication::Tick()
{
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
                            m_Config.appName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            m_Config.screenWidth + width_adjust,
                            m_Config.screenHeight + height_adjust,
                            NULL,
                            NULL,
                            hInstance,
                            this);

    ShowWindow(m_hWnd, SW_SHOW);
}