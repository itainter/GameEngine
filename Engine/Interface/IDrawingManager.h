#pragma once

#include "Global.h"

namespace Engine
{
    class IDrawingManager
    {
    public:
        IDrawingManager() = default;
        virtual ~IDrawingManager() = default;

        virtual void Flush() = 0;
        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual EDeviceType GetDeviceType() const = 0;
        virtual void SetDeviceType(EDeviceType type) = 0;
    };
}