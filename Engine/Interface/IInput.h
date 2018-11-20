#pragma once

#include <iostream>

#include "IRuntimeModule.h"
#include "IEvent.h"

namespace Engine
{
    enum EInputEvent
    {
        eEv_Input_Unknown = 100,

        eEv_Input_KeyDown = 101,
        eEv_Input_KeyUp = 102,
        eEv_Input_KeyDbClick = 103,

        eEv_Input_ControlMove = 111,
        eEv_Input_ControlLeave = 112,
        eEv_Input_ControlWheel = 113,
        eEv_Input_ControlHover = 114,
    };

    class IInputManager : public IRuntimeModule
    {
    public:
        virtual ~IInputManager() {};

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void Tick() = 0;
    };
}