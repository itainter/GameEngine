#pragma once

#include "DrawingResourceDesc.h"
#include "DrawingManager.h"

namespace Engine
{ 
    class IDrawingDevice
    {
    public:
        IDrawingDevice() = default;
        virtual ~IDrawingDevice() = default;
    };
}