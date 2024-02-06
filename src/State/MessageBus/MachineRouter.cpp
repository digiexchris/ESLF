#include "State/MessageBus/MachineRouter.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace MessageBus
{

void MachineRouter::on_receive(const MachineMessageInterface& msg)
{
    ELSF_LOG_INFO("MachineRouter received message %d", msg.get_message_id());
    myFsm->receive(msg);
}

void MachineRouter::on_receive_unknown(const etl::imessage& msg)
{
    ELSF_LOG_WARN("MachineRouter received unknown message with id %d", msg.get_message_id());
}

} // namespace Machine
} // namespace State

