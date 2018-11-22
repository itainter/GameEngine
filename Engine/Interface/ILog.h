#pragma once

#include "IRuntimeModule.h"

namespace Engine
{
    class ILog : public IRuntimeModule
    {
    public:
        virtual ~ILog() {}

        virtual void Initialize() override = 0;
        virtual void Shutdown() override = 0;

        virtual void Tick() override = 0;
    };
}