#include <memory>
#include <iostream>

#include "ILog.h"
#include "IEvent.h"
#include "InputLog.h"

using namespace Engine;

void InputLog::Initialize()
{
    m_LogInputKeyCharFunc = std::bind(&InputLog::OutputLogStream<eEv_Input_KeyChar>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyChar, m_LogInputKeyCharFunc);

    m_LogInputKeyDownFunc = std::bind(&InputLog::OutputLogStream<eEv_Input_KeyDown>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyDown, m_LogInputKeyDownFunc);

    m_LogInputKeyUpFunc = std::bind(&InputLog::OutputLogStream<eEv_Input_KeyUp>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyUp, m_LogInputKeyUpFunc);
}

void InputLog::Shutdown()
{
    DISPATCH_EVENT(eEv_Input_KeyChar, m_LogInputKeyCharFunc);
    DISPATCH_EVENT(eEv_Input_KeyDown, m_LogInputKeyDownFunc);
    DISPATCH_EVENT(eEv_Input_KeyUp, m_LogInputKeyUpFunc);
}

void InputLog::Tick()
{
}