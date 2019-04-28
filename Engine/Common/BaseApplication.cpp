#include <stdexcept>
#include <string>
#include <sstream>

#include "Global.h"
#include "IEventManager.h"
#include "IDrawingManager.h"
#include "ISceneManager.h"
#include "IInputManager.h"
#include "IlogManager.h"
#include "IECS.h"

#include "EventManager.h"
#include "SystemLog.h"
#include "InputLog.h"
#include "EntityPool.h"

#include "BaseApplication.h"

using namespace Engine;

bool BaseApplication::m_bQuit = false;

void BaseApplication::Initialize()
{
    m_pEventManager = gpGlobal->GetEventManager();
    m_pDrawingManager = gpGlobal->GetDrawingManager();
    m_pEntityPool = gpGlobal->GetEntityPool();
    m_pSceneManager = gpGlobal->GetSceneManager();
    m_pInputManager = gpGlobal->GetInputManager();
    m_pSystemLog = gpGlobal->GetLogSystem();
    m_pInputLog = gpGlobal->GetLogInput();

    std::ostringstream details;
    details << gpGlobal->GetConfiguration();

    DECLARE_EVENT(eEv_System_App, AppInitEvTitle, std::string("BaseApplication initialize"));
    DECLARE_EVENT(eEv_System_App, AppInitEvDetail, details.str());
    EMITTER_EVENT(AppInitEvTitle);
    EMITTER_EVENT(AppInitEvDetail);

    if (m_pEntityPool)
        m_pEntityPool->Initialize();

    if (m_pEventManager)
        m_pEventManager->Initialize();

    if (m_pSceneManager)
        m_pSceneManager->Initialize();

    if (m_pDrawingManager)
        m_pDrawingManager->Initialize();

    if (m_pInputManager)
        m_pInputManager->Initialize();

    if (m_pSystemLog)
        m_pSystemLog->Initialize();

    if (m_pInputLog)
        m_pInputLog->Initialize();
}

void BaseApplication::Shutdown()
{
    if (m_pInputLog)
        m_pInputLog->Shutdown();

    if (m_pSystemLog)
        m_pSystemLog->Shutdown();

    if (m_pInputManager)
        m_pInputManager->Shutdown();

    if (m_pDrawingManager)
        m_pDrawingManager->Shutdown();

    if (m_pSceneManager)
        m_pSceneManager->Shutdown();

    if (m_pEventManager)
        m_pEventManager->Shutdown();

    if (m_pEntityPool)
        m_pEntityPool->Shutdown();
}

void BaseApplication::Tick()
{
    gpGlobal->GetFPSCounter().BeginTick();

    if (m_pInputManager)
        m_pInputManager->Tick();

    if (m_pSystemLog)
        m_pSystemLog->Tick();

    if (m_pInputLog)
        m_pInputLog->Tick();

    if (m_pSceneManager)
        m_pSceneManager->Tick();

    if (m_pEntityPool)
        m_pEntityPool->Tick();

    if (m_pDrawingManager)
        m_pDrawingManager->Tick();

    if (m_pEventManager)
        m_pEventManager->Tick();

    gpGlobal->GetFPSCounter().EndTick();
}

bool BaseApplication::IsQuit() const
{
    return m_bQuit;
}