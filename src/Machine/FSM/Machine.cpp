
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "Machine.hpp"
#include "Idle.hpp"
#include "Turning.hpp"
#include "EStop.hpp"
#include "Logging/Logger.hpp"

namespace Machine
{
namespace FSM
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
  }

  void MachineFSM::ExecuteStartAt()
  {
  }

  void MachineFSM::ExecuteStop()
  {
  }

  void MachineFSM::ExecuteStopAt()
  {
  }

  void MachineFSM::ExecuteEStop()
  {
  }

  void MachineFSM::ExecuteReset()
  {
  }

} // namespace Machine
} // namespace State