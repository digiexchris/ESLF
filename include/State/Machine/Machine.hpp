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
  virtual void ExecuteStart();
  virtual void ExecuteStartAt();
  virtual void ExecuteStop();
  virtual void ExecuteStopAt();
  virtual void ExecuteEStop();
  virtual void ExecuteReset();

protected:


};


  } // namespace Machine
} // namespace State
