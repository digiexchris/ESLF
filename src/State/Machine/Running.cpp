
#include "etl/queue.h"
#include "etl/fsm.h"
#include "State/Machine/Machine.hpp"
#include "State/Machine/Running.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace Machine
{

  etl::fsm_state_id_t RunningState::on_enter_state()
  {
    ELSF_LOG_INFO(" S1 : Enter state RUNNING\n");
    return etl::ifsm_state::No_State_Change; //This MUST return No_State_Change using etl::hfsm
  }

  //***************************************************************************
  void RunningState::on_exit_state()
  {
    ELSF_LOG_INFO("  S1 : Exit state RUNNING\n");
  }

  etl::fsm_state_id_t RunningState::on_event(const StopMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message STOP\n");
    return MachineStateId::IDLE;
  }

  etl::fsm_state_id_t RunningState::on_event(const StopAtMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message STOP AT\n");
    return etl::ifsm_state::No_State_Change;
  }

  //***************************************************************************
  etl::fsm_state_id_t RunningState::on_event(const EStopMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP; //this should transition to the sub-state ESTOP of all movement mode states.
  }

  //***************************************************************************
  etl::fsm_state_id_t RunningState::on_event(const ResetMessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received message RESET\n");
    return MachineStateId::IDLE;
  }

  //***************************************************************************
  etl::fsm_state_id_t RunningState::on_event_unknown(const etl::imessage& msg)
  {
    ELSF_LOG_INFO("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
  }


} // namespace Machine
} // namespace State
