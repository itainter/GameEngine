#pragma once

#include <memory>
#include <string>
#include "IEvent.h"
#include "EventManager.h"

namespace Engine
{
    template <typename T, typename E, E e,
              typename = typename std::enable_if<std::is_enum<E>::value>::type>
    class Event : public IEventData
    {
    public:
        typedef T msg_t;

        Event() {}
        Event(const msg_t t, const char* n) : m_id(e), m_name(n), m_msg(t) {}

        id_t GetID()        override { return m_id; }
        name_t GetName()    override { return m_name; }
        msg_t GetMsg()               { return m_msg; }

    private:
        id_t m_id;
        name_t m_name;
        msg_t m_msg;
    };
}