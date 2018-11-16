#pragma once

#include <queue>

#include "IInput.h"

namespace Engine
{
    class InputMsg
    {
    public:
        InputMsg(size_t _ctrID, int _param1 = 0, int _param2 = 0) : ctrID(_ctrID), param1(_param1), param2(_param2) {}
        size_t CtrID() const { return ctrID; }
        int Param1() const { return param1; }
        int Param2() const { return param2; }
    private:
        size_t ctrID;
        int param1;
        int param2;
    };
    std::ostream& operator<< (std::ostream &out, InputMsg const& e);

    class Input : public IInput
    {
    public:
        Input() {};
        virtual ~Input() {};

        void Initialize() override;
        void Shutdown() override;
        void Tick() override;

        virtual void DispatchInputEvent(EInputEvent event, InputMsg msg);

    private:
        struct InputMsgInfo
        {
            InputMsgInfo(EInputEvent _event, InputMsg _msg) : event(_event), msg(_msg){}
            EInputEvent event;
            InputMsg msg;
        };
        std::queue<InputMsgInfo> m_inputQueue;
    };
}