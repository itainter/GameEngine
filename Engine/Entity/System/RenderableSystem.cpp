#include "RenderableSystem.h"

#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"

using namespace Engine;

void RenderableSystem::Initialize(std::shared_ptr<IEntity> pEntity)
{
    auto pTransformComp = pEntity->GetComponent<TransformComponent>();
    auto pMeshFilterComp = pEntity->GetComponent<MeshFilterComponent>();
    auto pMeshRendererComp = pEntity->GetComponent<MeshRendererComponent>();

    auto pRenderer = pMeshRendererComp->GetRenderer();
    pRenderer->AttachMesh(pMeshFilterComp->GetMesh());
}

void RenderableSystem::Update(std::shared_ptr<IEntity> pEntity)
{
}