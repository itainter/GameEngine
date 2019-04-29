#include <memory>
#include <iostream>

#include "ILogManager.h"
#include "IEventManager.h"
#include "SystemLog.h"

using namespace Engine;

void SystemLog::Initialize()
{
    m_logSystemEventFunc = std::bind(&SystemLog::OutputLogSystemStream, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_System_App, m_logSystemEventFunc);

    m_LogInputKeyCharFunc = std::bind(&SystemLog::OutputLogInputStream<eEv_Input_KeyChar>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyChar, m_LogInputKeyCharFunc);

    m_LogInputKeyDownFunc = std::bind(&SystemLog::OutputLogInputStream<eEv_Input_KeyDown>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyDown, m_LogInputKeyDownFunc);

    m_LogInputKeyUpFunc = std::bind(&SystemLog::OutputLogInputStream<eEv_Input_KeyUp>, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_Input_KeyUp, m_LogInputKeyUpFunc);
}

void SystemLog::Shutdown()
{
    DISPATCH_EVENT(eEv_System_App, m_logSystemEventFunc);
    DISPATCH_EVENT(eEv_Input_KeyChar, m_LogInputKeyCharFunc);
    DISPATCH_EVENT(eEv_Input_KeyDown, m_LogInputKeyDownFunc);
    DISPATCH_EVENT(eEv_Input_KeyUp, m_LogInputKeyUpFunc);
}

void SystemLog::Tick()
{
}

void SystemLog::OutputLogSystemStream(LogSystemEventPtr data) const
{
    std::cout << data->GetMsg() << std::endl;
}