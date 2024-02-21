
#include "etl/fsm.h"
#include "etl/message_packet.h"
#include "Machine/FSM/Machine.hpp"
#include "Machine/FSM/Idle.hpp"
#include "Logging/Logger.hpp"

namespace Machine
{
namespace FSM
{

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_enter_state()
  {
    ELSF_LOG_INFO("  S2 : Enter state Idle\n" );
    return etl::ifsm_state::No_State_Change; //Queue the message that sets the saved mode here if we want to restore mode on startup
  }

  void IdleState::on_exit_state()
  {
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const StartMessage& msg)
  {
    get_fsm_context().ExecuteStart();
    ELSF_LOG_INFO("  S1 : Received message START\n");
    return MachineStateId::RUNNING;
  }

  etl::fsm_state_id_t IdleState::on_event(const StartAtMessage& msg)
  {
    get_fsm_context().ExecuteStartAt();
    ELSF_LOG_INFO("  S1 : Received message START AT\n");
    return etl::ifsm_state::No_State_Change;
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const EStopMessage& msg)
  {
    get_fsm_context().ExecuteEStop();
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP;
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const ResetMessage& msg)
  {
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return etl::ifsm_state::No_State_Change; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event_unknown(const etl::imessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
  }

} // namespace Machine
} // namespace State
