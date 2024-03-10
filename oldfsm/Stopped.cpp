
#include "Stopped.hpp"
#include "Base.hpp"
#include "Logging/Logger.hpp"
#include <etl/fsm.h>
#include <etl/message_packet.h>
#include <etl/queue.h>

namespace Machine::FSM
{

etl::fsm_state_id_t StoppedState::on_enter_state()
{
    ELSF_LOG_INFO("  S2 : Enter state Idle\n");
    return etl::ifsm_state::No_State_Change; // Queue the message that sets the saved mode
}

void StoppedState::on_exit_state()
{
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
}

//***************************************************************************
etl::fsm_state_id_t StoppedState::on_event(const MessageBus::ResetMessage&)
{
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return MachineStateId::IDLE;
}

//***************************************************************************
etl::fsm_state_id_t StoppedState::on_event(const MessageBus::StartMessage&)
{
    get_fsm_context().ExecuteStart();
    ELSF_LOG_INFO("  S1 : Received message START\n");
    return MachineStateId::MOVING;
}

etl::fsm_state_id_t StoppedState::on_event(const MessageBus::EStopMessage&)
{
    get_fsm_context().ExecuteEStop();
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP;
}

//***************************************************************************
etl::fsm_state_id_t StoppedState::on_event_unknown(const etl::imessage& msg)
{
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
}

} // namespace Machine::FSM
