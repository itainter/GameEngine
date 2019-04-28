#pragma once

#include "IRuntimeModule.h"
#include "Global.h"

namespace Engine
{
    class IDrawingManager : public IRuntimeModule
    {
    public:
        IDrawingManager() = default;
        virtual ~IDrawingManager() = default;

        virtual void Initialize() override = 0;
        virtual void Shutdown() override = 0;

        virtual void Tick() override = 0;

        virtual void Flush() = 0;
        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual EDeviceType GetDeviceType() const = 0;
        virtual void SetDeviceType(EDeviceType type) = 0;
    };
}