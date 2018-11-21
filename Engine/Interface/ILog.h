#pragma once

#include "IRuntimeModule.h"

namespace Engine
{
    class ILog : public IRuntimeModule
    {
    public:
        virtual ~ILog() {}

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void Tick() = 0;
    };
}