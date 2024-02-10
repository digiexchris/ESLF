
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "State/Machine/Machine.hpp"

namespace State {
namespace Machine {

  Machine::Machine()
    : hfsm(MACHINE_ROUTER_ID)
  {
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