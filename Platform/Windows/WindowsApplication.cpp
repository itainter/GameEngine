#include <memory>
#include "WindowsApplication.h"
#include <Windows.h>

using namespace Engine;
using namespace Platform;

namespace Engine
{
    WindowsApplication g_App;
    std::unique_ptr<IApplication> g_pApp = std::make_unique<WindowsApplication>(g_App);
}

/*void WindowsApplication::Initialize()
{
    
}

void WindowsApplication::Shutdown()
{
}

void WindowsApplication::Tick()
{
}

bool WindowsApplication::IsQuit() const
{
    return false;
}*/
