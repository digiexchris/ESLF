
#include "Moving.hpp"
#include "Base.hpp"
#include "Logging/Logger.hpp"
#include <etl/fsm.h>
#include <etl/message_packet.h>
#include <etl/queue.h>

namespace Machine::FSM
{

etl::fsm_state_id_t MovingState::on_enter_state()
{
    ELSF_LOG_INFO("  S2 : Enter state Idle\n");
    get_fsm_context().ExecuteStart();
    return etl::ifsm_state::No_State_Change; // Queue the message that sets the saved mode
}

void MovingState::on_exit_state()
{
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
}

//***************************************************************************
etl::fsm_state_id_t MovingState::on_event(const MessageBus::ResetMessage&)
{
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return MachineStateId::IDLE;
}

//***************************************************************************
etl::fsm_state_id_t MovingState::on_event(const MessageBus::StopMessage&)
{
    get_fsm_context().ExecuteStop();
    ELSF_LOG_INFO("  S1 : Received message STOP\n");
    return MachineStateId::STOPPED;
}

etl::fsm_state_id_t MovingState::on_event(const MessageBus::EStopMessage&)
{
    get_fsm_context().ExecuteEStop();
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP; // this should transition to the sub-state ESTOP of all movement
                                  // mode states.
}

//***************************************************************************
etl::fsm_state_id_t MovingState::on_event_unknown(const etl::imessage& msg)
{
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
}

} // namespace Machine::FSM
