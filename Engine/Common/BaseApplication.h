#pragma once

#include <string>

#include "IApplication.h"

namespace Engine
{
    enum ESystemEvent
    {
        eEv_System_AppLog = 1,
    };

    class IInputManager;
    class ILog;
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
        std::shared_ptr<IEventManager> m_pEventManager;
        std::shared_ptr<IInputManager> m_pInputManager;
        std::shared_ptr<ILog> m_pLog;
    };
}