#pragma once
#include "Base.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include <etl/fsm.h>

namespace Machine::FSM
{

class MovingState
    : public etl::fsm_state<BaseFSM, MovingState, MachineStateId::MOVING, MessageBus::ResetMessage,
                            MessageBus::StopMessage, MessageBus::EStopMessage>
{
public:
    etl::fsm_state_id_t on_enter_state() override;
    void on_exit_state() override;
    etl::fsm_state_id_t on_event(const MessageBus::ResetMessage& msg);
    etl::fsm_state_id_t on_event(const MessageBus::StopMessage& msg);
    etl::fsm_state_id_t on_event(const MessageBus::EStopMessage& msg);
    etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

} // namespace Machine::FSM