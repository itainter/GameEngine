#include "EntityPool.h"
#include "Entity.h"

using namespace Engine;

std::shared_ptr<IEntity> EntityPool::CreateEntity(const std::vector<IComponent*>& pComponents, const std::vector<CompID>& ids)
{
    std::shared_ptr<IEntity> pEntity = std::make_shared<EntityBase>(std::shared_ptr<EntityPool>(this));
    pEntity->m_id = (EntityID)m_entityPool.size();

    for (uint32_t i = 0; i < pComponents.size(); i++)
        pEntity->AttachComponent(ids[i], pComponents[i], m_compTable);

    m_entityPool.emplace_back(pEntity);
    return pEntity;
}