#pragma once

#include <etl/fsm.h>
#include "Machine/MessageBus/Messages.hpp"
#include "Machine.hpp"

namespace Machine
{
namespace FSM
{

using namespace MessageBus;
  //TODO rename from RunnmingState to TurningState or ThreadingState.
  //TODO the states should extend from Planner or planner from the states or maybe it's in the FSM itself? Yes, maybe the fsm.
  //The states maybe should only handle transitions and events.
  //TODO the states should have child states containing Running, Stopped, EStop, etc.
class TurningState : public etl::fsm_state<MachineFSM, TurningState, MachineStateId::TURNING, StopMessage, StopAtMessage, EStopMessage, ResetMessage>
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