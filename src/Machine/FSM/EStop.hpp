#pragma once
#include <etl/fsm.h>
#include "Machine/MessageBus/Messages.hpp"
#include "Machine.hpp"

namespace Machine
{
namespace FSM
{

using namespace ::Machine::MessageBus;

class EStopState : public etl::fsm_state<MachineFSM, EStopState, MachineStateId::ESTOP, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine
} // namespace State