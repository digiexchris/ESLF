#pragma once

#include <etl/hfsm.h>
#include <etl/message_packet.h>

#define MACHINE_ROUTER_ID 0

namespace Machine
{
namespace FSM
{

class TurningState;
class IdleState;
class EStopState;

enum MachineStateId
{
  IDLE,
  // THREADING,
  TURNING,
  ESTOP,
  NUMBER_OF_STATES
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class MachineFSM : public etl::hfsm
{
public:

  MachineFSM();
  virtual void ExecuteStart();
  virtual void ExecuteStartAt();
  virtual void ExecuteStop();
  virtual void ExecuteStopAt();
  virtual void ExecuteEStop();
  virtual void ExecuteReset();

protected:
  void Init();
  static IdleState idleState;
  static TurningState turningState;
  //static ThreadingState threadingState;
  static EStopState eStopState;
  //note, these need to be in the same order as in the enum MachineStateId
  static etl::ifsm_state* myStateList[3];//= { &idleState, &runningState, &eStopState };
};

  } // namespace Machine
} // namespace State
