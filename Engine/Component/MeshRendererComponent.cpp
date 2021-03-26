#include <assert.h>

#include "MeshRendererComponent.h"

using namespace Engine;

MeshRendererComponent::MeshRendererComponent() : ComponentBase<MeshRendererComponent>(),
    m_materialSize(0)
{
    m_pMaterialList.clear();
}

MeshRendererComponent::~MeshRendererComponent()
{
}

uint32_t MeshRendererComponent::GetMaterialSize() const
{
    return m_materialSize;
}

void MeshRendererComponent::SetMaterialSize(uint32_t size)
{
    m_materialSize = size;
    m_pMaterialList.resize(m_materialSize);
}

IMaterial* MeshRendererComponent::GetMaterial(uint32_t index) const
{
    if (m_materialSize == 0)
        return nullptr;

    assert(index < m_materialSize);
    return m_pMaterialList[index];
}

void MeshRendererComponent::SetMaterial(IMaterial* pMaterial, uint32_t index)
{
    assert(index < m_materialSize);
    m_pMaterialList[index] = pMaterial;
}