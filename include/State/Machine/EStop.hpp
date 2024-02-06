#pragma once
#include <etl/fsm.h>
#include "State/MessageBus/Messages.hpp"
#include "State/Machine/Machine.hpp"

namespace State
{
namespace Machine
{

using namespace MessageBus;

class EStopState : public etl::fsm_state<Machine, EStopState, MachineStateId::ESTOP, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine
} // namespace State