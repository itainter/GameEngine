#include "EventManager.h"

using namespace Engine;

bool EventManager::AddListener(IEventData::id_t id, EventDelegate proc)
{
    auto it = m_eventListeners.find(id);
    if (it == m_eventListeners.end())
        m_eventListeners[id] = EventDelegateList();
    
    auto &list = m_eventListeners[id];
    for (auto &p : list)
    {
        if (p.target<EventDelegate>() == proc.target<EventDelegate>())
            return false;
    }
    list.push_back(proc);

    return true;
}

bool EventManager::RemoveListener(IEventData::id_t id, EventDelegate proc)
{
    auto it = m_eventListeners.find(id);
    if (it == m_eventListeners.end())
        return false;

    auto &list = it->second;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        EventDelegate &p = *it; 
        if (p.target<EventDelegate>() == proc.target<EventDelegate>())
        {
            list.erase(it);
            return true;
        }
    }
    return false;
}

void EventManager::QueueEvent(IEventDataPtr e)
{
    m_eventQueue.push_back(e);
}

void EventManager::ProcessEvents()
{
    for (auto it = m_eventQueue.begin(); it != m_eventQueue.end();)
    {
        auto &e = *it;
        auto listeners = m_eventListeners.find(e->GetID());
        if (listeners != m_eventListeners.end())
        {
            for (auto p : listeners->second)
                p(e);
        }
        it = m_eventQueue.erase(it);
    }
}

EventListener::~EventListener()
{
    if (el_mEventManager.expired())
        return;
    auto em = el_mEventManager.lock();
    for (auto &e : el_mEvent)
        em->RemoveListener(e.first, e.second);
}

bool EventListener::OnEvent(IEventData::id_t id, EventDelegate proc)
{
    if(el_mEventManager.expired())
        return false; 
    auto em = el_mEventManager.lock(); 
    if (em->AddListener(id, proc)){
        el_mEvent.push_back(EventPair(id, proc)); 
    }
    return true;
}

bool EventListener::Dispatch(IEventData::id_t id, EventDelegate proc)
{
    if(el_mEventManager.expired())
        return false; 
    auto em = el_mEventManager.lock(); 
    em->RemoveListener(id, proc);
    return true;
}