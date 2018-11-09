#pragma once

#include "BaseApplication.h"

namespace Platform
{
    class WindowsApplication : public Engine::BaseApplication
    {
    public:
        WindowsApplication() {};
        virtual ~WindowsApplication() {};

        //void Initialize() override;
        //void Shutdown() override;

        //void Tick() override;

        //bool IsQuit() const override;
    };
}