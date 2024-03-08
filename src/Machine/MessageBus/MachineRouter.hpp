#pragma once

#include "Machine/FSM/Base.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "Machine/MessageBus/Router.hpp"

#include <etl/hfsm.h>

namespace Machine::MessageBus
{

// NOTE TO CHRIS. THIS IS THE ROUTER THAT THE BROKER CALLS, STOP TRYING TO MAKE IT THE BROKER
class MachineRouter
    : public Machine::MessageBus::QueuedRouter<MachineRouter,
                                               10, // Queue Depth
                                               StartMessage, StopMessage, SetTurningMode,
                                               EStopMessage, ResetMessage>
{
public:
    explicit MachineRouter(Machine::FSM::BaseFSM* fsm);
    MachineRouter() = default;

    void SetFsm(Machine::FSM::BaseFSM* anFsm)
    {
        myFsm = anFsm;
    };

    void Start();
    virtual void on_receive(const etl::imessage& msg);
    virtual void on_receive_unknown(const etl::imessage& msg);
    FSM::BaseFSM* GetFsm()
    {
        return myFsm;
    }

private:
    FSM::BaseFSM* myFsm;
};

} // namespace Machine::MessageBus