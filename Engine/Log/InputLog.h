#pragma once

#include <functional>

#include "ILog.h"
#include "Global.h"
#include "Input.h"

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
        auto msg = data->GetMsg();
        std::cout << "Key Char: "<< msg << " Character: " << static_cast<char>(msg.Param1()) << std::endl;
    };

    template<>
    inline void InputLog::OutputLogStream<eEv_Input_KeyDown>(LogInputKeyDownPtr data) const
    {
        std::cout << "Key Down: " << data->GetMsg() << std::endl;
    };

    template<>
    inline void InputLog::OutputLogStream<eEv_Input_KeyUp>(LogInputKeyUpPtr data) const
    {
        std::cout << "Key Up: " << data->GetMsg() << std::endl;
    };
}