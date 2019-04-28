#include "Global.h"

#include "IApplication.h"
#include "IEventManager.h"
#include "IInputManager.h"
#include "IDrawingManager.h"
#include "ISceneManager.h"
#include "IlogManager.h"
#include "IECS.h"
#include "IRenderer.h"

using namespace Engine;

namespace Engine
{
    Global* gpGlobal;
}

Global::~Global()
{
    m_RTModuleMap.clear();
}

std::shared_ptr<IApplication> Global::GetApplication()
{
    return GetRuntimeModule<IApplication>(eRTModule_App);
}

std::shared_ptr<IEntityPool> Global::GetEntityPool()
{
    return GetRuntimeModule<IEntityPool>(eRTModule_Entity_Pool);
}

std::shared_ptr<IEventManager> Global::GetEventManager()
{
    return GetRuntimeModule<IEventManager>(eRTModule_EventManager);
}

std::shared_ptr<IDrawingManager> Global::GetDrawingManager()
{
    return GetRuntimeModule<IDrawingManager>(eRTModule_DrawingManager);
}

std::shared_ptr<ISceneManager> Global::GetSceneManager()
{
    return GetRuntimeModule<ISceneManager>(eRTModule_SceneManager);
}

std::shared_ptr<IInputManager> Global::GetInputManager()
{
    return GetRuntimeModule<IInputManager>(eRTModule_InputManager);
}

std::shared_ptr<ILog> Global::GetLogSystem()
{
    return GetRuntimeModule<ILog>(eRTModule_Log_System);
}

std::shared_ptr<ILog> Global::GetLogInput()
{
    return GetRuntimeModule<ILog>(eRTModule_Log_Input);
}

std::shared_ptr<IRenderer> Global::GetRenderer(ERTModule module)
{
    assert((module >= eRTModule_Renderer_Begin) && (module <= eRTModule_Renderer_End));
    return GetRuntimeModule<IRenderer>(module);
}

Configuration& Global::GetConfiguration()
{
    return m_config;
}

FPSCounter& Global::GetFPSCounter()
{
    return m_fps;
}

Setup::Setup()
{
    if (gpGlobal == nullptr)
        gpGlobal = new Global();
}