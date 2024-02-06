
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "State/Machine/Machine.hpp"

namespace State {
namespace Machine {

  Machine::Machine()
    : hfsm(MACHINE_ROUTER_ID)
  {
  }

} // namespace Machine
} // namespace State