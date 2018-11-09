#pragma once

#include <string>
#include "IApplication.h"
#include "IEvent.h"
#include "ILog.h"

namespace Engine
{
    enum ESystemEvent
    {
        eLogStream = 1,
    };

    class BaseApplication : public IApplication
    {
    public:
        BaseApplication() {};
        virtual ~BaseApplication() {};

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

        bool IsQuit() const override;

    private:
        std::shared_ptr<ILog> m_pLog;
    };
}