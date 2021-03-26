#include "SkyboxComponent.h"

using namespace Engine;

SkyboxComponent::SkyboxComponent()
{
}

std::shared_ptr<SkyboxMaterial> SkyboxComponent::GetSkyboxMaterial() const
{
    return m_pSkyboxMaterial;
}

void SkyboxComponent::SetSkyboxMaterial(std::shared_ptr<SkyboxMaterial> pMaterial)
{
    m_pSkyboxMaterial = pMaterial;
}