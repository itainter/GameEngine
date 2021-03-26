#pragma once

#include "IMaterial.h"

namespace Engine
{
    class SkyboxMaterial : public IMaterial
    {
    public:
        SkyboxMaterial();
        virtual ~SkyboxMaterial();
    };

    class SkyboxPanoramicMaterial : public SkyboxMaterial
    {
    public:
        SkyboxPanoramicMaterial();
        virtual ~SkyboxPanoramicMaterial();

        EMaterialType GetMaterialType() const override
        {
            return eMaterial_Skybox_Panoramic;
        }

        std::shared_ptr<ITexture> GetHDRMap() const;
        void SetHDRMap(std::shared_ptr<ITexture> map);

    protected:
        std::shared_ptr<ITexture> m_pHDRMap;
    };
}