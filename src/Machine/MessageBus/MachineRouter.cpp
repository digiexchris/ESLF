#include "Machine/MessageBus/MachineRouter.hpp"
#include "Logging/Logger.hpp"
#include "Machine/MessageBus/Messages.hpp"

namespace Machine
{
namespace MessageBus
{
    MachineRouter::MachineRouter(Machine::FSM::MachineFSM& fsm) : myFsm(fsm)
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

