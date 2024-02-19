
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "State/Machine/Machine.hpp"
#include "State/Machine/Idle.hpp"
#include "State/Machine/Running.hpp"
#include "State/Machine/EStop.hpp"


namespace State {
namespace Machine {

  IdleState Machine::idleState;
  RunningState Machine::runningState;
  EStopState Machine::eStopState;
  etl::ifsm_state* Machine::myStateList[] = { &idleState, &runningState, &eStopState };

  Machine::Machine()
    : hfsm(MACHINE_ROUTER_ID)
  {
    set_states(myStateList, 3);
  }

  void Machine::ExecuteStart()
  {
  }

  void Machine::ExecuteStartAt()
  {
  }

  void Machine::ExecuteStop()
  {
  }

  void Machine::ExecuteStopAt()
  {
  }

  void Machine::ExecuteEStop()
  {
  }

  void Machine::ExecuteReset()
  {
  }

} // namespace Machine
} // namespace State