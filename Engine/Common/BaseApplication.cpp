#include <stdexcept>
#include <string>

#include "Global.h"
#include "IEvent.h"
#include "IInput.h"
#include "Ilog.h"

#include "EventManager.h"
#include "SystemLog.h"
#include "InputLog.h"

#include "BaseApplication.h"

using namespace Engine;

bool BaseApplication::m_bQuit = false;

void BaseApplication::Initialize()
{
    m_pEventManager = gpGlobal->GetEventManager();
    m_pInputManager = gpGlobal->GetInputManager();
    m_pSystemLog = gpGlobal->GetLogSystem();
    m_pInputLog = gpGlobal->GetLogInput();

    DECLARE_EVENT(eEv_System_App, AppInitEv, std::string("BaseApplication initialize"));
    EMITTER_EVENT(AppInitEv);

    if (m_pEventManager)
        m_pEventManager->Initialize();

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

    if (m_pEventManager)
        m_pEventManager->Shutdown();
}

void BaseApplication::Tick()
{
    if (m_pInputManager)
        m_pInputManager->Tick();

    if (m_pSystemLog)
        m_pSystemLog->Tick();

    if (m_pInputLog)
        m_pInputLog->Tick();

    if (m_pEventManager)
        m_pEventManager->Tick();
}

bool BaseApplication::IsQuit() const
{
    return m_bQuit;
}