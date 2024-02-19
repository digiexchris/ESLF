#include "State/MessageBus/MachineRouter.hpp"
#include "Logging/Logger.hpp"
#include "State/MessageBus/Messages.hpp"

namespace State
{
namespace MessageBus
{
    MachineRouter::MachineRouter(State::Machine::Machine& fsm) : myFsm(fsm)
    {
        myFsm.start();
    }

    void MachineRouter::on_receive(const etl::imessage& msg)
    {
        myFsm.receive(msg);
        ELSF_LOG_INFO("MachineRouter received message: $d", msg.get_message_id());
    }

    void MachineRouter::on_receive_unknown(const etl::imessage& msg)
    {
        ELSF_LOG_WARN("MachineRouter received unknown message. This shouldn't happen because of the broker.");
    }

} // namespace Machine
} // namespace State

