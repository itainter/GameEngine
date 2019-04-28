#pragma once

#include <functional>

#include "ILogManager.h"
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
        typedef Event<std::string, ESystemEvent, eEv_System_App> LogSystemEvent;
        typedef std::shared_ptr<LogSystemEvent> LogSystemEventPtr;
        typedef std::function<void(LogSystemEventPtr)> LogSystemEventFunc;
    
        void OutputLogStream(LogSystemEventPtr data) const;

    private:
        DECLARE_LISTENER();
        LogSystemEventFunc m_logSystemEventFunc;
    };
}