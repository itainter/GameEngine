#pragma once

#include <memory>
#include <list>
#include <string>
#include <functional>

namespace Engine
{
    class IEventData
    {
    public:
        typedef size_t id_t;
        typedef std::string name_t;

        virtual id_t GetID() = 0;
        virtual name_t GetName() = 0;
    };

    typedef std::shared_ptr<IEventData> IEventDataPtr;
    typedef std::function<void(IEventDataPtr&)> EventDelegate;
    typedef std::list<EventDelegate> EventDelegateList;
    typedef uintptr_t EventListenerAddr;

    class IEventManager
    {
    public:
        virtual bool AddListener(IEventData::id_t id, EventDelegate proc) = 0;
        virtual bool RemoveListener(IEventData::id_t id, EventDelegate proc) = 0;
        virtual void QueueEvent(IEventDataPtr e) = 0;
        virtual void ProcessEvents() = 0;
    };
}