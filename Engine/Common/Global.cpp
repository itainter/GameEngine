#include "Global.h"

#include "IApplication.h"
#include "IEvent.h"
#include "IInput.h"
#include "Ilog.h"

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
    return GetRuntimeModule<IApplication, eRTModule_App>();
}

std::shared_ptr<IEventManager> Global::GetEventManager()
{
    return GetRuntimeModule<IEventManager, eRTModule_EventManager>();
}

std::shared_ptr<IInputManager> Global::GetInputManager()
{
    return GetRuntimeModule<IInputManager, eRTModule_InputManager>();
}

std::shared_ptr<ILog> Global::GetSystemLog()
{
    return GetRuntimeModule<ILog, eRTModule_SystemLog>();
}

Configuration& Global::GetConfiguration()
{
    return m_config;
}

Setup::Setup()
{
    if (gpGlobal == nullptr)
        gpGlobal = new Global();
}