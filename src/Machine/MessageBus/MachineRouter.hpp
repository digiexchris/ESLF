#pragma once

#include "Machine/MessageBus/Messages.hpp"
#include "Machine/FSM/Machine.hpp"
#include "Machine/MessageBus/Router.hpp"

#include <etl/hfsm.h>

namespace Machine::MessageBus
{


//NOTE TO CHRIS. THIS IS THE ROUTER THAT THE BROKER CALLS, STOP TRYING TO MAKE IT THE BROKER
class MachineRouter 
    : public Machine::MessageBus::QueuedRouter<
    MachineRouter, 
    10, //Queue Depth
    StartMessage,
    StopMessage,
    SetTurningMode,
    EStopMessage, 
    ResetMessage>
{
public:
    explicit MachineRouter(Machine::FSM::MachineFSM* fsm);
    //warning: you must call start manually if you use the default constructor, after setting the FSM.
    MachineRouter() = default;

    void SetFsm(Machine::FSM::MachineFSM* anFsm){ 
        myFsm.reset(anFsm);
    };

    void Start();
    virtual void on_receive(const etl::imessage& msg);
    virtual void on_receive_unknown(const etl::imessage& msg);
    FSM::MachineFSM* GetFsm() { return myFsm.get(); }

private:
    etl::unique_ptr<FSM::MachineFSM> myFsm;
};

} // namespace Machine::MessageBus