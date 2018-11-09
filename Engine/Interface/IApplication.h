#pragma once

#include <memory>
#include "IRuntimeModule.h"

namespace Engine
{
    class IApplication : public IRuntimeModule
    {
    public:
        virtual ~IApplication() {};

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void Tick() = 0;

        virtual bool IsQuit() const = 0;
    };
}