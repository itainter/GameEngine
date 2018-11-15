#include <memory>
#include <Windows.h>

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
