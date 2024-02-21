#pragma once

#include <etl/fsm.h>
#include "Machine/MessageBus/Messages.hpp"
#include "Machine/FSM/Machine.hpp"

namespace Machine
{
namespace FSM
{

using namespace MessageBus;

class RunningState : public etl::fsm_state<MachineFSM, RunningState, MachineStateId::RUNNING, StopMessage, StopAtMessage, EStopMessage, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const StopMessage& msg);
  etl::fsm_state_id_t on_event(const StopAtMessage& msg);
  etl::fsm_state_id_t on_event(const EStopMessage& msg);
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine
} // namespace State