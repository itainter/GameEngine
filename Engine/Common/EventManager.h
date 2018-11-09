#pragma once

#include <map>
#include <vector>
#include <memory>
#include "Traits.h"
#include "IEvent.h"

namespace Engine
{
    class EventManager : public IEventManager
    {
    public:
        static std::shared_ptr<IEventManager> Get()
        {
            static std::shared_ptr<IEventManager> em(new EventManager);
            return em;
        }
        virtual ~EventManager() {}

        bool AddListener(IEventData::id_t id, EventDelegate proc) override;
        bool RemoveListener(IEventData::id_t id, EventDelegate proc) override;
        void QueueEvent(IEventDataPtr e) override;
        void ProcessEvents() override;

    protected:
        EventManager() {}

    private:
        std::list<IEventDataPtr> m_eventQueue;
        std::map<IEventData::id_t, EventDelegateList> m_eventListeners;
    };

    class EventListener
    {
    public:
        EventListener() : el_mEventManager(EventManager::Get()) {}
        virtual ~EventListener();

        template<class T>
        bool OnEvent(IEventData::id_t id, std::function<void(std::shared_ptr<T>)> proc)
        {
            return OnEvent(id, [&, proc](IEventDataPtr data){
                auto ev = std::dynamic_pointer_cast<T>(data); 
                if(ev) proc(ev);
            }); 
        }
        template<class T>
        bool Dispatch(IEventData::id_t id, std::function<void(std::shared_ptr<T>)> proc)
        {
            return Dispatch(id, [&, proc](IEventDataPtr data){
                auto ev = std::dynamic_pointer_cast<T>(data); 
                if(ev) proc(ev); 
            });
        }

    protected:
        typedef std::pair<IEventData::id_t, EventDelegate> EventPair;
        bool OnEvent(IEventData::id_t id, EventDelegate proc);
        bool Dispatch(IEventData::id_t id, EventDelegate proc);

    private:
        std::weak_ptr<IEventManager> el_mEventManager;
        std::vector<EventPair> el_mEvent;
    }; 

#define DECLARE_EVENT(id, event, msg)                                                               \
    Event<decltype(msg), decltype(id), id> event(msg, #id)

#define EMITTER_EVENT(event)                                                                        \
    EventManager::Get()->QueueEvent(std::shared_ptr<IEventData>(new decltype(event)(event)))

#define DECLARE_LISTENER()                                                                          \
    EventListener listener

#define LISTEN_EVENT(id, func)                                                                     \
    {                                                                                               \
        auto f = func;                                                                              \
        typedef function_traits<decltype(f)> traits;                                                \
        listener.OnEvent<traits::arg<0>::type::element_type>(id, func);                             \
    }                                                                                               \

#define DISPATCH_EVENT(id, func)                                                                    \
    {                                                                                               \
        auto f = func;                                                                              \
        typedef function_traits<decltype(f)> traits;                                                \
        listener.Dispatch<traits::arg<0>::type::element_type>(id, func);                            \
    }

}