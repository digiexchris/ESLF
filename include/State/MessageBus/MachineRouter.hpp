#pragma once

#include "State/MessageBus/Router.hpp"
#include "State/MessageBus/Messages.hpp"
#include "State/Machine/Machine.hpp"

#include <etl/hfsm.h>

namespace State
{
namespace MessageBus
{

class MachineRouter 
    : public State::MessageBus::QueuedRouter<
    MachineRouter, 
    10, 
    StartMessage, 
    StartAtMessage, 
    StopMessage, 
    StopAtMessage, 
    EStopMessage, 
    ResetMessage>
{
public:
    MachineRouter(State::Machine::Machine* fsm) : myFsm(fsm)
    {
    }
    void on_receive(const MachineMessageInterface& msg);

    void on_receive_unknown(const etl::imessage& msg);

private:
    etl::hfsm* myFsm;
};

} // namespace Machine
} // namespace State