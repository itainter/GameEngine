#pragma once

#include <string>

#include "IApplication.h"

namespace Engine
{
    enum ESystemEvent
    {
        eEv_System_App = 1,
    };

    class IDrawingManager;
    class ISceneManager;
    class IInputManager;
    class ILog;
    class BaseApplication : public IApplication
    {
    public:
        BaseApplication() {}
        virtual ~BaseApplication() {}

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

        bool IsQuit() const override;

    protected:
        static bool m_bQuit;
        std::shared_ptr<IECSWorld> m_pWorld;
    };
}