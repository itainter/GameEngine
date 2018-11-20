#include <stdexcept>
#include <string>

#include "Global.h"
#include "IEvent.h"
#include "IInput.h"
#include "Ilog.h"

#include "EventManager.h"
#include "SystemLog.h"

#include "BaseApplication.h"

using namespace Engine;

void BaseApplication::Initialize()
{
    m_pEventManager = gpGlobal->GetEventManager();
    m_pInputManager = gpGlobal->GetInputManager();
    m_pLog = gpGlobal->GetSystemLog();

    DECLARE_EVENT(eEv_System_AppLog, AppInitEv, std::string("BaseApplication initialize"));
    EMITTER_EVENT(AppInitEv);

    if (m_pEventManager)
        m_pEventManager->Initialize();

    if (m_pInputManager)
        m_pInputManager->Initialize();

    if (m_pLog)
        m_pLog->Initialize();
}

void BaseApplication::Shutdown()
{
    if (m_pLog)
        m_pLog->Shutdown();

    if (m_pInputManager)
        m_pInputManager->Shutdown();

    if (m_pEventManager)
        m_pEventManager->Shutdown();
}

void BaseApplication::Tick()
{
    if (m_pEventManager)
        m_pEventManager->Tick();

    if (m_pInputManager)
        m_pInputManager->Tick();

    if (m_pLog)
        m_pLog->Tick();

    gpGlobal->GetEventManager()->ProcessEvents();
}

bool BaseApplication::IsQuit() const
{
    return false;
}