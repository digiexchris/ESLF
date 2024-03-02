
#include "etl/queue.h"
#include "etl/fsm.h"
#include "Machine/FSM/Machine.hpp"
#include "Machine/FSM/Turning.hpp"
#include "Logging/Logger.hpp"

namespace Machine::FSM
{

  etl::fsm_state_id_t TurningState::on_enter_state()
  {
    ELSF_LOG_INFO(" S1 : Enter state RUNNING\n");
    return etl::ifsm_state::No_State_Change; //This MUST return No_State_Change using etl::hfsm
  }

  //***************************************************************************
  void TurningState::on_exit_state()
  {
    ELSF_LOG_INFO("  S1 : Exit state RUNNING\n");
  }

  etl::fsm_state_id_t TurningState::on_event(const MessageBus::StopMessage& msg)
  {
    get_fsm_context().ExecuteStop();
    ELSF_LOG_INFO("  S1 : Received message STOP\n");
    return MachineStateId::IDLE;
  }

  //***************************************************************************
  etl::fsm_state_id_t TurningState::on_event(const MessageBus::EStopMessage& msg)
  {
    get_fsm_context().ExecuteEStop();
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP; //this should transition to the sub-state ESTOP of all movement mode states.
  }

  //***************************************************************************
  etl::fsm_state_id_t TurningState::on_event(const MessageBus::ResetMessage& msg)
  {
    get_fsm_context().ExecuteReset();
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return MachineStateId::IDLE;
  }

  //***************************************************************************
  etl::fsm_state_id_t TurningState::on_event_unknown(const etl::imessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
  }


} // namespace Machine::FSM
