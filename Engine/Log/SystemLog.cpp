#include <memory>
#include <iostream>
#include "Event.h"
#include "EventManager.h"
#include "SystemLog.h"

using namespace Engine;

void SystemLog::Initialize()
{
    m_logStreamEventFunc = std::bind(&SystemLog::OutputLogStream, this, std::placeholders::_1);
    LISTEN_EVENT(eEv_System_AppLog, m_logStreamEventFunc);
}

void SystemLog::Shutdown()
{
    DISPATCH_EVENT(eEv_System_AppLog, m_logStreamEventFunc);
}

void SystemLog::OutputLogStream(LogStreamEventPtr data)
{
    std::cout << data->GetMsg() << std::endl;
}