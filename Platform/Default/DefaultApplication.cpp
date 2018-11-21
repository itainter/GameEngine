#include <memory>

#include "Global.h"
#include "BaseApplication.h"
#include "EventManager.h"
#include "Input.h"
#include "SystemLog.h"

namespace Engine
{
    class DefaultSetup : public Setup
    {
    public:
        DefaultSetup()
        {
            gpGlobal->RegisterRuntimeModule<BaseApplication, eRTModule_App>();
            gpGlobal->RegisterRuntimeModule<EventManager, eRTModule_EventManager>();
            gpGlobal->RegisterRuntimeModule<InputManager, eRTModule_InputManager>();
            gpGlobal->RegisterRuntimeModule<SystemLog, eRTModule_Log_System>();
        }
    };

    DefaultSetup setup;
}