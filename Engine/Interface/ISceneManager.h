#pragma once

#include "IRuntimeModule.h"

namespace Engine
{
    class ISceneManager : public IRuntimeModule
    {
    public:
        ISceneManager() = default;
        virtual ~ISceneManager() = default;

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void Tick() = 0;
    };
}