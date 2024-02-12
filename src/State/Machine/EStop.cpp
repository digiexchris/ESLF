
#include <etl/queue.h>
#include <etl/fsm.h>
#include <etl/message_packet.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/EStop.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace Machine
{

etl::fsm_state_id_t EStopState::on_enter_state()
  {
    ELSF_LOG_INFO("  S2 : Enter state Idle\n" );
    return etl::ifsm_state::No_State_Change; //Queue the message that sets the saved mode
  }

  void EStopState::on_exit_state()
  {
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t EStopState::on_event(const ResetMessage& msg)
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


} // namespace Machine
} // namespace State
