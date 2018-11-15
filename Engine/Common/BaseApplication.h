#pragma once

#include <string>
#include "IApplication.h"
#include "IEvent.h"
#include "IInput.h"
#include "ILog.h"

namespace Engine
{
    enum ESystemEvent
    {
        eEv_System_AppLog = 1,
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
        std::shared_ptr<IInput> m_pInput;
        std::shared_ptr<ILog> m_pLog;
    };
}