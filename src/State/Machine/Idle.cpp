
#include "etl/fsm.h"
#include "etl/message_packet.h"
#include "State/Machine/Machine.hpp"
#include "State/Machine/Idle.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace Machine
{

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_enter_state()
  {
    ELSF_LOG_INFO("  S2 : Enter state Idle\n" );
    return etl::ifsm_state::No_State_Change; //Queue the message that sets the saved mode
  }

  void IdleState::on_exit_state()
  {
    ELSF_LOG_INFO("  S2 : Exit state Idle\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const StartMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message START\n");
    return MachineStateId::RUNNING;
  }

  etl::fsm_state_id_t IdleState::on_event(const StartAtMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message START AT\n");
    return etl::ifsm_state::No_State_Change; //TODO return the child state WAITING_FOR_SYNC
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const EStopMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP;
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const ResetMessage& msg)
  {
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
