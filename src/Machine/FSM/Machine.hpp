#pragma once

#include <etl/hfsm.h>
#include <etl/message_packet.h>

#define MACHINE_ROUTER_ID 0

namespace Machine::FSM
{

class TurningState;
class IdleState;
class EStopState;
class MovingState;
class StoppedState;

enum MachineStateId
{
  IDLE,
  // THREADING,
  TURNING,
  ESTOP,
  MOVING,
  STOPPED,
  NUMBER_OF_STATES
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class MachineFSM : public etl::hfsm
{
public:

  MachineFSM();
  virtual void ExecuteSetTurnMode();
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
  static EStopState eStopState;
  static StoppedState stoppedState;
  static MovingState movingState;
  //note, these need to be in the same order as in the enum MachineStateId
  static etl::ifsm_state* myStateList[5];
  static etl::ifsm_state* myTurningChildStateList[2];
};

  } // namespace Machine::FSM
