#pragma once

#include "ECSSystem.h"

#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"

#include "DrawingManager.h"

namespace Engine
{
    class RenderableSystem : public ECSSystemBase<TransformComponent, MeshFilterComponent, MeshRendererComponent>
    {
    public:
        RenderableSystem() {}
        virtual ~RenderableSystem() = default;

        void Initialize(std::shared_ptr<IEntity> pEntity) override;
        void Update(std::shared_ptr<IEntity> pEntity) override;
    };
}