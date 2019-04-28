#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "IRuntimeModule.h"

namespace Engine
{
    class IComponent;
    class IEntity;
    class IEntityPool;

    typedef uint32_t CompID;
    typedef uint32_t CompIndex;
    typedef uint64_t CompBitset;

    typedef CompIndex(*CreateCompFunc)(IComponent*, std::shared_ptr<IEntity>, std::vector<uint8_t>&);
    typedef void(*DestroyCompFunc)(IComponent*);

    typedef uint32_t EntityID;

    class IComponent : public std::enable_shared_from_this<IComponent>
    {
    public:
        IComponent() = default;
        ~IComponent() = default;

        typedef std::tuple<CreateCompFunc, DestroyCompFunc, uint32_t> CompType;
        typedef std::vector<CompType> CompTableType;

        static uint32_t RegisterComponent(CreateCompFunc createFunc, DestroyCompFunc destroyFunc, uint32_t size);

        static CreateCompFunc GetCreateFunc(uint32_t id)
        {
            return std::get<0>(m_compTable[id]);
        }

        static DestroyCompFunc GetDestroyFunc(uint32_t id)
        {
            return std::get<1>(m_compTable[id]);
        }

        static uint32_t GetSize(uint32_t id)
        {
            return std::get<2>(m_compTable[id]);
        }

        static void ClearComponentTable()
        {
            m_compTable.clear();
        }

    public:
        std::shared_ptr<IEntity> m_pEntity = nullptr;

    private:
        static CompTableType m_compTable;
    };

    class IEntity : public std::enable_shared_from_this<IEntity>
    {
    public:
        IEntity(std::shared_ptr<IEntityPool> pool) : m_pEntityPool(pool), m_compBitset(0) {}
        virtual ~IEntity() = default;

        virtual void AttachComponent(CompID compId, IComponent* pComponent, std::unordered_map<CompID, std::vector<uint8_t>>& memory) = 0;
        virtual void DetachComponent(CompID compId, CompIndex compIndex, std::unordered_map<CompID, std::vector<uint8_t>>& memory) = 0;

        template<typename Comp>
        inline Comp* GetComponent();

    public:
        EntityID m_id;

    protected:
        std::shared_ptr<IEntityPool> m_pEntityPool;
        CompBitset m_compBitset;
        std::vector<std::pair<CompID, CompIndex>> m_comps;
    };

    template<typename Comp>
    inline Comp* IEntity::GetComponent()
    {
        CompID compId = Comp::m_compID;
        CompIndex compIndex = 0;
        bool bFound = false;
        for(auto comp : m_comps)
            if (compId == comp.first)
            {
                compIndex = comp.second;
                bFound = true;
                break;
            }
        if (!bFound)
            return nullptr;

        Comp* pComp = (Comp*)(&m_pEntityPool->m_compTable[compId][compIndex]);
        return pComp;
    };

    class IECSSystem
    {
    public:
        IECSSystem() : m_compBitset(0) {}
        virtual ~IECSSystem() = default;

        virtual void Initialize(std::shared_ptr<IEntity> pEntity) = 0;
        virtual void Update(std::shared_ptr<IEntity> pEntity) = 0;

    protected:
        CompBitset m_compBitset;
        std::vector<CompID> m_comps;
    };

    class IEntityPool : public IRuntimeModule
    {
    friend IEntity;
    public:
        template<typename ...Comps>
        std::shared_ptr<IEntity> CreateEntity(Comps... comps);

        template<typename... Comps>
        std::shared_ptr<IEntity> CreateEntity();

        void AddECSSystem(std::shared_ptr<IECSSystem> pSystem);
        void RemoveECSSystem(std::shared_ptr<IECSSystem> pSystem);

        void Initialize() override 
        {
            for (uint32_t i = 0; i < m_entityPool.size(); i++)
                for (uint32_t j = 0; j < m_systemPool.size(); j++)
                    m_systemPool[j]->Initialize(m_entityPool[i]);
        }

        void Shutdown() override {}

        void Tick() override
        {
            for (uint32_t i = 0; i < m_entityPool.size(); i++)
                for (uint32_t j = 0; j < m_systemPool.size(); j++)
                    m_systemPool[j]->Update(m_entityPool[i]);
        }

    private:
        virtual std::shared_ptr<IEntity> CreateEntity(const std::vector<IComponent*>& pComponents, const std::vector<CompID>& ids) = 0;

    protected:
        std::unordered_map<CompID, std::vector<uint8_t>> m_compTable;
        std::vector<std::shared_ptr<IEntity>> m_entityPool;
        std::vector<std::shared_ptr<IECSSystem>> m_systemPool;
    };

    template<typename ...Comps>
    inline std::shared_ptr<IEntity> IEntityPool::CreateEntity(Comps... comps)
    {
        std::vector<CompID> ids = { Comps::m_compID... };
        std::vector<IComponent*> pComponents = { &comps... };
        auto pEntity = CreateEntity(pComponents, ids);
        return pEntity;
    }

    template<typename... Comps>
    inline std::shared_ptr<IEntity> IEntityPool::CreateEntity()
    {
        std::vector<CompID> ids = { Comps::m_compID... };
        std::vector<IComponent*> pComponents = { new Comps()... };
        auto pEntity = CreateEntity(pComponents, ids);
        return pEntity;
    }

    inline void IEntityPool::AddECSSystem(std::shared_ptr<IECSSystem> pSystem)
    {
        m_systemPool.push_back(pSystem);
    }

    inline void IEntityPool::RemoveECSSystem(std::shared_ptr<IECSSystem> pSystem)
    {
        for(uint32_t i = 0; i < m_systemPool.size(); i++)
        {
            if (m_systemPool[i] == pSystem)
            {
                m_systemPool[i] = m_systemPool[m_systemPool.size() - 1];
                m_systemPool.pop_back();
            }
        }
    }
}