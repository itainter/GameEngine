#pragma once

#include <memory>

#include "ITexture.h"
#include "Vector.h"

namespace Engine
{
    enum EMaterialType
    {
        eMaterial_Standard = 0,

        eMaterial_Skybox_Panoramic,
    };

    class IMaterial
    {
    public:
        IMaterial() {}
        virtual ~IMaterial() = default;

        virtual EMaterialType GetMaterialType() const = 0;
    };
}