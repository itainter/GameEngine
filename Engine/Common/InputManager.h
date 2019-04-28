#pragma once

#include <queue>
#include <stdint.h>

#include "IInputManager.h"

namespace Engine
{
    class InputManager : public IInputManager
    {
    public:
        InputManager() {}
        virtual ~InputManager() {}

        void Initialize() override;
        void Shutdown() override;
        void Tick() override;

        void DispatchInputEvent(EInputEvent event, InputMsg msg) override;

    private:
        struct InputMsgInfo
        {
            InputMsgInfo(EInputEvent _event, InputMsg _msg) : event(_event), msg(_msg){}
            EInputEvent event;
            InputMsg msg;
        };
        std::queue<InputMsgInfo> m_inputQueue;
    };
}