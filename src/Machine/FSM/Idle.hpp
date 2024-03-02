#pragma once
#include <etl/fsm.h>
#include "Machine/MessageBus/Messages.hpp"
#include "Machine.hpp"

namespace Machine::FSM
{

class IdleState : public etl::fsm_state<MachineFSM, IdleState, MachineStateId::IDLE, MessageBus::SetTurningMode, MessageBus::EStopMessage, MessageBus::ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const MessageBus::SetTurningMode& msg);
  etl::fsm_state_id_t on_event(const MessageBus::EStopMessage& msg);
  etl::fsm_state_id_t on_event(const MessageBus::ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine::FSM