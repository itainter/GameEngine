#include <stdexcept>
#include <string>

#include "Event.h"
#include "EventManager.h"
#include "Input.h"
#include "SystemLog.h"

#include "BaseApplication.h"

using namespace Engine;

void BaseApplication::Initialize()
{
    m_pInput = std::shared_ptr<IInput>(new Input());
    m_pLog = std::shared_ptr<ILog>(new SystemLog());

    DECLARE_EVENT(eEv_System_AppLog, AppInitEv, std::string("BaseApplication initialize"));
    EMITTER_EVENT(AppInitEv);

    m_pInput->Initialize();
    m_pLog->Initialize();
}

void BaseApplication::Shutdown()
{
    m_pLog->Shutdown();
    m_pInput->Shutdown();
}

void BaseApplication::Tick()
{
    m_pInput->Tick();
    EventManager::Get()->ProcessEvents();
}

bool BaseApplication::IsQuit() const
{
    return false;
}