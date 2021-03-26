#include "SkyboxMaterial.h"

using namespace Engine;

SkyboxMaterial::SkyboxMaterial()
{
}

SkyboxMaterial::~SkyboxMaterial()
{
}

SkyboxPanoramicMaterial::SkyboxPanoramicMaterial()
{
}

SkyboxPanoramicMaterial::~SkyboxPanoramicMaterial()
{
}

std::shared_ptr<ITexture> SkyboxPanoramicMaterial::GetHDRMap() const
{
    return m_pHDRMap;
}

void SkyboxPanoramicMaterial::SetHDRMap(std::shared_ptr<ITexture> map)
{
    m_pHDRMap = map;
}