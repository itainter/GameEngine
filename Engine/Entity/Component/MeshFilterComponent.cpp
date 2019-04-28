#include "MeshFilterComponent.h"

using namespace Engine;

std::shared_ptr<IMesh> MeshFilterComponent::GetMesh()
{
    return m_pMesh;
}

void MeshFilterComponent::SetMesh(std::shared_ptr<IMesh> pMesh)
{
    m_pMesh = pMesh;
}