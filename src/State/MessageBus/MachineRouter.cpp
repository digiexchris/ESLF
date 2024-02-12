#include "State/MessageBus/MachineRouter.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace MessageBus
{
    void MachineRouter::on_receive(const StartMessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received StartMessage");
    }

    void MachineRouter::on_receive(const StartAtMessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received StartAtMessage");
    }

    void MachineRouter::on_receive(const StopMessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received StopMessage");
    }

    void MachineRouter::on_receive(const StopAtMessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received StopAtMessage");
    }

    void MachineRouter::on_receive(const EStopMessage& msg)
    {
        //?? the event? I guess? Fire off to the FSM?
        ELSF_LOG_INFO("MachineRouter received EStopMessage");
    }

    void MachineRouter::on_receive(const ResetMessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received ResetMessage");
    }

    void MachineRouter::on_receive_unknown(const etl::imessage& msg)
    {
        ELSF_LOG_INFO("MachineRouter received unknown message. This shouldn't happen because of the broker.");
    }

} // namespace Machine
} // namespace State

