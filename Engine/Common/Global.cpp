#include "Global.h"

#include "IApplication.h"
#include "IECSWorld.h"
#include "IRenderer.h"

#include "IEventManager.h"
#include "IDrawingManager.h"
#include "ISceneManager.h"
#include "IInputManager.h"
#include "ILogManager.h"

using namespace Engine;

namespace Engine
{
    Global* gpGlobal;
}

Global::Global()
{
}

Global::~Global()
{
    m_pRenderers.clear();
    m_pSystems.clear();
}

std::shared_ptr<IApplication> Global::GetApplication()
{
    return m_pApp;
}

std::shared_ptr<IECSWorld> Global::GetECSWorld()
{
    return m_pWorld;
}

std::shared_ptr<IEventManager> Global::GetEventManager()
{
    auto& pModule = GetRuntimeModule(eSystem_EventManager);
    auto pEventManager = std::dynamic_pointer_cast<IEventManager>(pModule);
    return pEventManager;
}

std::shared_ptr<IDrawingManager> Global::GetDrawingManager()
{
    auto& pModule = GetRuntimeModule(eSystem_DrawingManager);
    auto pDrawingManager = std::dynamic_pointer_cast<IDrawingManager>(pModule);
    return pDrawingManager;
}

std::shared_ptr<ISceneManager> Global::GetSceneManager()
{
    auto& pModule = GetRuntimeModule(eSystem_SceneManager);
    auto pSceneManager = std::dynamic_pointer_cast<ISceneManager>(pModule);
    return pSceneManager;
}

std::shared_ptr<IInputManager> Global::GetInputManager()
{
    auto& pModule = GetRuntimeModule(eSystem_InputManager);
    auto pInputManager = std::dynamic_pointer_cast<IInputManager>(pModule);
    return pInputManager;
}

std::shared_ptr<ILog> Global::GetLogSystem()
{
    auto& pModule = GetRuntimeModule(eSystem_Log_System);
    auto pLogSystem = std::dynamic_pointer_cast<ILog>(pModule);
    return pLogSystem;
}

std::shared_ptr<IRenderer> Global::GetRenderer(ERendererType type)
{
    auto it = m_pRenderers.find(type);
    if (it == m_pRenderers.end())
        return nullptr;
    else
    {
        auto& renderer = it->second;
        auto result = std::dynamic_pointer_cast<IRenderer>(renderer);
        return result;
    }
}

Configuration& Global::GetConfiguration()
{
    return m_config;
}

FPSCounter& Global::GetFPSCounter()
{
    return m_fps;
}

std::shared_ptr<IECSSystem> Global::GetRuntimeModule(ESystemType e)
{
    auto it = m_pSystems.find(e);
    if (it == m_pSystems.end())
        return nullptr;
    else
    {
        auto& system = it->second;
        auto result = std::dynamic_pointer_cast<IECSSystem>(system);
        return result;
    }
}

Setup::Setup()
{
    if (gpGlobal == nullptr)
        gpGlobal = new Global();
}