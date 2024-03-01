

#include "etl/hfsm.h"
#include "etl/message_packet.h"
#include <etl/utility.h>

#include "Machine.hpp"
#include "Idle.hpp"
#include "Turning.hpp"
#include "EStop.hpp"
#include "Stopped.hpp"
#include "Moving.hpp"
#include "Logging/Logger.hpp"

namespace Machine::FSM
{

  IdleState MachineFSM::idleState;
  TurningState MachineFSM::turningState;
  EStopState MachineFSM::eStopState;
  MovingState MachineFSM::movingState;
  StoppedState MachineFSM::stoppedState;
  etl::ifsm_state* MachineFSM::myTurningChildStateList[] = {&stoppedState, &movingState};

  //note, these states must exist in the same order as they're defined in the enum!!!
  etl::ifsm_state* MachineFSM::myStateList[] = { &idleState, &turningState, &eStopState, &movingState, &stoppedState  };
  
  MachineFSM::MachineFSM()
    : hfsm(MACHINE_ROUTER_ID)
  {
    turningState.set_child_states(myTurningChildStateList, 2);
    set_states(myStateList, 5);
  }

  void MachineFSM::ExecuteSetTurnMode()
  {
    auto test = 0;
    //set turn mode settings appropriate, like the allowable error creep, and wether we can move along Z at any time or if it's locked until the cut is done
  }

  void MachineFSM::ExecuteStart()
  {
    //will be implemented later
  }

  void MachineFSM::ExecuteStartAt()
  {
    //will be implemented later
  }

  void MachineFSM::ExecuteStop()
  {
    //will be implemented later
  }

  void MachineFSM::ExecuteStopAt()
  {
    //will be implemented later
  }

  void MachineFSM::ExecuteEStop()
  {
    //will be implemented later
  }

  void MachineFSM::ExecuteReset()
  {
    //will be implemented later
  }

} // namespace Machine::FSM