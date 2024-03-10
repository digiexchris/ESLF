
#include "EStop.hpp"
#include "Base.hpp"
#include "Logging/Logger.hpp"
#include <etl/fsm.h>
#include <etl/message_packet.h>
#include <etl/queue.h>

namespace Machine::FSM
{

etl::fsm_state_id_t EStopState::on_enter_state()
{
    ELSF_LOG_INFO("  S2 : Enter state EStop\n");
    auto& context = get_fsm_context();
    context.ExecuteEStop();
    return etl::ifsm_state::No_State_Change;
}

void EStopState::on_exit_state()
{
    ELSF_LOG_INFO("  S2 : Exit state EStop\n");
}

//***************************************************************************
etl::fsm_state_id_t EStopState::on_event(const MessageBus::ResetMessage& msg)
{
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return MachineStateId::IDLE;
}

//***************************************************************************
etl::fsm_state_id_t EStopState::on_event_unknown(const etl::imessage& msg)
{
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
}

} // namespace Machine::FSM
