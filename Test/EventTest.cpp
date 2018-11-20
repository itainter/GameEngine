#include <string>
#include <memory>
#include <iostream>

#include "Global.h"
#include "IEvent.h"
#include "EventManager.h"

using namespace Engine;

namespace Engine
{
    class TestSetup : public Setup
    {
    public:
        TestSetup()
        {
            gpGlobal->RegisterRuntimeModule<EventManager, eRTModule_EventManager>();
        }
    };

    TestSetup setup;
}

enum ETestEvent
{
    eTestEvent_1 = 1,
    eTestEvent_2 = 2,
    eTestEvent_3 = 3
};

struct EventData
{
    EventData(int _val, std::string _data) : val(_val), data(_data) {}

    int val;
    std::string data;

    friend std::ostream& operator<< (std::ostream &out, EventData const& d)
    {
        return out << "(val: " << d.val << ", data: " << d.data << ")";
    }
};

int main()
{
    DECLARE_LISTENER();
    {
        LISTEN_EVENT(eTestEvent_1, [&](std::shared_ptr<Event<std::string, ETestEvent, eTestEvent_1>> data){
            std::cout << "Listen 1: " << data->GetMsg() << std::endl;
        });
        LISTEN_EVENT(eTestEvent_2, [&](std::shared_ptr<Event<EventData, ETestEvent, eTestEvent_2>> data){
            std::cout << "Listen 2: " << data->GetMsg() << std::endl;
        });
        LISTEN_EVENT(eTestEvent_3, [&](std::shared_ptr<Event<EventData, ETestEvent, eTestEvent_3>> data){
            std::cout << "Listen 3: " << data->GetMsg() << std::endl;
        });
    }

    {
        DECLARE_EVENT(eTestEvent_1, TestEvent_1, std::string("This is TestEvent_1"));

        DECLARE_EVENT(eTestEvent_2, TestEvent_2_1, EventData(201, "This is TestEvent_2_1"));
        DECLARE_EVENT(eTestEvent_2, TestEvent_2_2, EventData(202, "This is TestEvent_2_2"));
        DECLARE_EVENT(eTestEvent_2, TestEvent_2_3, EventData(202, "This is TestEvent_2_3"));

        DECLARE_EVENT(eTestEvent_3, TestEvent_3, EventData(300, "This is TestEvent_3"));

        for(int i = 0; i < 2; i++)
            EMITTER_EVENT(TestEvent_1);

        EMITTER_EVENT(TestEvent_2_1);
        EMITTER_EVENT(TestEvent_2_2);

        EMITTER_EVENT(TestEvent_3);
    }

    gpGlobal->GetEventManager()->ProcessEvents();

    return 0;
}