#pragma once

#include <etl/hfsm.h>
#include <etl/message_packet.h>

#define MACHINE_ROUTER_ID 0

namespace State
{
namespace Machine
{


enum MachineStateId
{
  IDLE,
  RUNNING,
  ESTOP,
  NUMBER_OF_STATES
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class Machine : public etl::hfsm
{
public:

  Machine();

protected:


};


  } // namespace Machine
} // namespace State