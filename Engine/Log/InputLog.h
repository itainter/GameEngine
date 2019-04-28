#pragma once

#include <functional>

#include "ILogManager.h"
#include "Global.h"
#include "InputManager.h"

namespace Engine
{
    class InputLog : public ILog
    {
    public:
        InputLog() {}
        virtual ~InputLog() {}

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

    private:
        #define DEF_InputEventType(event, enum)                                         \
            typedef Event<InputMsg, EInputEvent, enum> event;                           \
            typedef std::shared_ptr<event> event##Ptr;                                  \
            typedef std::function<void(event##Ptr)> event##Func;                        \
            event##Func m_##event##Func

        DEF_InputEventType(LogInputKeyChar, eEv_Input_KeyChar);
        DEF_InputEventType(LogInputKeyDown, eEv_Input_KeyDown);
        DEF_InputEventType(LogInputKeyUp, eEv_Input_KeyUp);
        DEF_InputEventType(LogInputKeyDbClick, eEv_Input_KeyDbClick);

        DEF_InputEventType(LogInputControlMove, eEv_Input_ControlMove);
        DEF_InputEventType(LogInputControlLeave, eEv_Input_ControlLeave);
        DEF_InputEventType(LogInputControlWheel, eEv_Input_ControlWheel);
        DEF_InputEventType(LogInputControlHover, eEv_Input_ControlHover);

        template<EInputEvent e>
        inline void OutputLogStream(std::shared_ptr<Event<InputMsg, EInputEvent, e>> data) const {};

    private:
        DECLARE_LISTENER();
    };

    template<>
    inline void InputLog::OutputLogStream<eEv_Input_KeyChar>(LogInputKeyCharPtr data) const
    {
        auto c = static_cast<char>(data->GetMsg().Param1());
        switch (c)
        {
            case 'f':
                std::cout << "Avg FPS: " <<
                            gpGlobal->GetFPSCounter().GetFPSAvgSec() << ", " <<
                            "Cur FPS: " <<
                            gpGlobal->GetFPSCounter().GetFPSCurrent() << std::endl;
            break;
        }
    };

    template<>
    inline void InputLog::OutputLogStream<eEv_Input_KeyDown>(LogInputKeyDownPtr data) const
    {
    };

    template<>
    inline void InputLog::OutputLogStream<eEv_Input_KeyUp>(LogInputKeyUpPtr data) const
    {
    };
}