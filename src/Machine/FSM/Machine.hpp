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
  virtual void ExecuteStop();
  virtual void ExecuteEStop();
  virtual void ExecuteReset();

  etl::fsm_state_id_t GetStateId() const;

protected:
  void Init();
  static IdleState idleState;
  static TurningState turningState;
  static EStopState eStopState;
  static StoppedState stoppedState;
  static MovingState movingState;
  //note, these need to be in the same order as in the enum MachineStateId
  static etl::array<etl::ifsm_state*, 5> myStateList;
  static etl::array<etl::ifsm_state*, 2> myTurningChildStateList;
};

  } // namespace Machine::FSM
