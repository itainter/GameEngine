#pragma once

#include "Component.h"
#include "SkyboxMaterial.h"

namespace Engine
{
    class SkyboxComponent : public ComponentBase<SkyboxComponent>
    {
    public:
        SkyboxComponent();
        virtual ~SkyboxComponent() = default;

        std::shared_ptr<SkyboxMaterial> GetSkyboxMaterial() const;
        void SetSkyboxMaterial(std::shared_ptr<SkyboxMaterial> pMaterial);

    private:
        std::shared_ptr<SkyboxMaterial> m_pSkyboxMaterial;
    };
}