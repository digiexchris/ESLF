#pragma once
#include <etl/fsm.h>
#include "Machine/MessageBus/Messages.hpp"
#include "Machine.hpp"

namespace Machine::FSM
{

class MovingState : public etl::fsm_state<MachineFSM, MovingState, MachineStateId::MOVING, MessageBus::ResetMessage, MessageBus::StopMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const MessageBus::ResetMessage& msg);
  etl::fsm_state_id_t on_event(const MessageBus::StopMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine::FSM