#include "IInput.h"
#include "EventManager.h"
#include "Input.h"

using namespace Engine;

std::ostream& operator<< (std::ostream &out, InputMsg const& e)
{
    return out << "(control ID: " << e.CtrID() << ", param 1: " << e.Param1() << ", param 2: " << e.Param2() << ")" << std::endl;
}

void InputManager::Initialize()
{
}

void InputManager::Shutdown()
{
    while (!m_inputQueue.empty())
        m_inputQueue.pop();
}

void InputManager::Tick()
{
    while (!m_inputQueue.empty())
    {
        auto info = m_inputQueue.front();
        switch(info.event)
        {
            case eEv_Input_KeyDown:
            {
                DECLARE_EVENT(eEv_Input_KeyDown, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_KeyUp:
            {
                DECLARE_EVENT(eEv_Input_KeyDown, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_KeyDbClick:
            {
                DECLARE_EVENT(eEv_Input_KeyDbClick, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_ControlMove:
            {
                DECLARE_EVENT(eEv_Input_ControlMove, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_ControlLeave:
            {
                DECLARE_EVENT(eEv_Input_ControlLeave, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_ControlWheel:
            {
                DECLARE_EVENT(eEv_Input_ControlWheel, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            case eEv_Input_ControlHover:
            {
                DECLARE_EVENT(eEv_Input_ControlHover, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
            default:
            {
                DECLARE_EVENT(eEv_Input_Unknown, inputEvent, info.msg);
                EMITTER_EVENT(inputEvent);
                break;
            }
        }
    }
}

void InputManager::DispatchInputEvent(EInputEvent event, InputMsg msg)
{
    m_inputQueue.push(InputMsgInfo(event, msg));
}