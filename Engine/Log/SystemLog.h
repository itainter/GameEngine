#pragma once

#include <functional>

#include "ILog.h"
#include "Global.h"
#include "BaseApplication.h"
namespace Engine
{
    class SystemLog : public ILog
    {
    public:
        SystemLog() {}
        virtual ~SystemLog() {}

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

    private:
        typedef Event<std::string, ESystemEvent, eEv_System_AppLog> LogStreamEvent;
        typedef std::shared_ptr<LogStreamEvent> LogStreamEventPtr;
        typedef std::function<void(LogStreamEventPtr)> LogStreamEventFunc;
    
        void OutputLogStream(LogStreamEventPtr data);

    private:
        DECLARE_LISTENER();
        LogStreamEventFunc m_logStreamEventFunc;
    };
}