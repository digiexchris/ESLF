
#include "Idle.hpp"
#include "Base.hpp"
#include "Logging/Logger.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "etl/fsm.h"
#include "etl/message_packet.h"

namespace Machine::FSM
{

//***************************************************************************
etl::fsm_state_id_t IdleState::on_enter_state()
{
    ELSF_LOG_INFO("  S2 : Enter state Idle\n");
    return etl::ifsm_state::No_State_Change; // Queue the message that sets the saved mode here if
                                             // we want to restore mode on startup
}

void IdleState::on_exit_state()
{
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
}

//***************************************************************************
etl::fsm_state_id_t IdleState::on_event(const MessageBus::SetTurningMode&)
{
    ELSF_LOG_INFO("  S1 : Received message TURNING\n");
    return MachineStateId::STOPPED;
}

//***************************************************************************
etl::fsm_state_id_t IdleState::on_event(const MessageBus::EStopMessage&)
{
    get_fsm_context().ExecuteEStop();
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP;
}

//***************************************************************************
etl::fsm_state_id_t IdleState::on_event(const MessageBus::ResetMessage&)
{
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return etl::ifsm_state::No_State_Change; // uhh, maybe we don't need this message, but I need to
                                             // play with the FSM
}

//***************************************************************************
etl::fsm_state_id_t IdleState::on_event_unknown(const etl::imessage& msg)
{
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
}

} // namespace Machine::FSM
