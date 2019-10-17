#pragma once

#include <memory>

#include "ITexture.h"
#include "Vector.h"

namespace Engine
{
    class IMaterial
    {
    public:
        IMaterial() {}
        
        virtual ~IMaterial() = default;
    };
}