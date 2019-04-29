#pragma once

#include <map>
#include <memory>

#include "IEventManager.h"

#include "ECSSystem.h"

namespace Engine
{
    class EventManager : public IEventManager, public ECSSystemBase<>
    {
    public:
        EventManager() {}
        virtual ~EventManager() {}

        void Initialize() override;
        void Shutdown() override;
        void Tick() override;

        bool AddListener(IEventData::id_t id, EventDelegate proc) override;
        bool RemoveListener(IEventData::id_t id, EventDelegate proc) override;
        void QueueEvent(IEventDataPtr e) override;

    protected:
        void ProcessEvents() override;

    private:
        std::list<IEventDataPtr> m_eventQueue;
        std::map<IEventData::id_t, EventDelegateList> m_eventListeners;
    };
}