

#include "etl/hfsm.h"
#include "etl/message_packet.h"
#include <etl/utility.h>

#include "Base.hpp"
#include "EStop.hpp"
#include "Idle.hpp"
#include "Logging/Logger.hpp"
#include "Moving.hpp"
#include "Stopped.hpp"
#include "Turning.hpp"

namespace Machine::FSM
{

IdleState BaseFSM::idleState;
TurningState BaseFSM::turningState;
EStopState BaseFSM::eStopState;
MovingState BaseFSM::movingState;
StoppedState BaseFSM::stoppedState;
etl::array<etl::ifsm_state*, 2> BaseFSM::myTurningChildStateList = {&stoppedState, &movingState};

// note, these states must exist in the same order as they're defined in the enum!!!
etl::array<etl::ifsm_state*, 5> BaseFSM::myStateList = {&idleState, &turningState, &eStopState,
                                                        &movingState, &stoppedState};

BaseFSM::BaseFSM() : hfsm(MACHINE_ROUTER_ID)
{
    Start();
}

void BaseFSM::Start()
{
    if (is_started())
    {
        return;
    }

    turningState.set_child_states(myTurningChildStateList.data(), 2);
    set_states(myStateList.data(), 5);
	start();
}

void BaseFSM::ExecuteSetTurnMode()
{
    EnableMotors();
}

void BaseFSM::ExecuteStart()
{
    EnableMotors();
}

void BaseFSM::ExecuteStop()
{
    // will be implemented later
}

void BaseFSM::ExecuteEStop()
{
    DisableMotors();
}

void BaseFSM::ExecuteReset()
{
    // will be implemented later
}
etl::fsm_state_id_t BaseFSM::GetStateId() const
{
    return get_state_id();
}

} // namespace Machine::FSM