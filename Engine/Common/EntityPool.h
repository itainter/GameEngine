#pragma once

#include "IECS.h"

namespace Engine
{
    class EntityPool : public IEntityPool
    {
    public:
        EntityPool() = default;

    protected:
        std::shared_ptr<IEntity> CreateEntity(const std::vector<IComponent*>& pComponents, const std::vector<CompID>& ids) override;
    };
}
