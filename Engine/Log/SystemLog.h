#pragma once

#include "ILog.h"
#include "BaseApplication.h"
#include "EventManager.h"

namespace Engine
{
    class SystemLog : public ILog
    {
    public:
        SystemLog() {}
        virtual ~SystemLog() {}

        void Initialize() override;
        void Shutdown() override;

    private:
        typedef Event<std::string, ESystemEvent, eLogStream> LogStreamEvent;
        typedef std::shared_ptr<LogStreamEvent> LogStreamEventPtr;
        typedef std::function<void(LogStreamEventPtr)> LogStreamEventFunc;
    
        void OutputLogStream(LogStreamEventPtr data);

    private:
        DECLARE_LISTENER();
        LogStreamEventFunc m_logStreamEventFunc;
    };
}