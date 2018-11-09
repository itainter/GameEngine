#include <stdexcept>
#include <string>
#include "Event.h"
#include "EventManager.h"
#include "SystemLog.h"
#include "BaseApplication.h"

using namespace Engine;

void BaseApplication::Initialize()
{
    m_pLog = std::shared_ptr<ILog>(new SystemLog());

    DECLARE_EVENT(eLogStream, MyEvent, std::string("BaseApplication::Initialize"));
    EMITTER_EVENT(MyEvent);

    m_pLog->Initialize();
}

void BaseApplication::Shutdown()
{
}

void BaseApplication::Tick()
{
    EventManager::Get()->ProcessEvents();
}

bool BaseApplication::IsQuit() const
{
    return false;
}