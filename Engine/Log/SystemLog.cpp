#include <memory>
#include <iostream>

#include "ILogManager.h"
#include "IEventManager.h"
#include "SystemLog.h"

using namespace Engine;

void SystemLog::Initialize()
{
    m_logSystemEventFunc = std::bind(&SystemLog::OutputLogStream, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_System_App, m_logSystemEventFunc);
}

void SystemLog::Shutdown()
{
    DISPATCH_EVENT(eEv_System_App, m_logSystemEventFunc);
}

void SystemLog::Tick()
{
}

void SystemLog::OutputLogStream(LogSystemEventPtr data) const
{
    std::cout << data->GetMsg() << std::endl;
}