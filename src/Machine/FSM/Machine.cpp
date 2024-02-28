
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "Machine.hpp"
#include "Idle.hpp"
#include "Turning.hpp"
#include "EStop.hpp"
#include "Logging/Logger.hpp"

namespace Machine::FSM
{

  IdleState MachineFSM::idleState;
  TurningState MachineFSM::turningState;
  EStopState MachineFSM::eStopState;
  etl::ifsm_state* MachineFSM::myStateList[] = { &idleState, &turningState, &eStopState };
  
  MachineFSM::MachineFSM()
    : hfsm(MACHINE_ROUTER_ID)
  {
    set_states(myStateList, 3);
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