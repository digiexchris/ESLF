
# FSM state hierarchy:
- Movement (root)
    - Idle
    - Slotting
    - EStop
    - Turning
        - Waiting
        - ReturnToStart
            - RetractingForReturn
            - MovingToStart
        - WaitingForSync
            - UnretractForPass
            - Waiting
        - TurnToDestination
            - Moving
            - Retracting


#
```mermaid
stateDiagram
    [*] --> Idle
    
    Idle --> Slotting :SetSlottingModeEvent
    Idle --> EStop :EStopEvent
    Idle --> Turning :SetTurnModeEvent
    Turning --> WaitForUser :Initial State
    WaitForuser --> Waiting :Initial State in WaitForuser
    Waiting --> ReturnToStart : ReturnToStartEvent
    ReturnToStart --> RetractingForReturn :Internal Transition or Retract Event from Initial State
    RetractingForReturn --> MovingToStart :MoveDoneEvent
    MovingToStart --> Waiting :MoveDoneEvent

    Waiting --> WaitForSync :NextPassEvent
    WaitForSync --> UnretractForPass
    UnretractForPass --> Waiting :MoveDoneEvent
    Waiting --> TurningToDestination :InSyncEvent
    TurningToDestination --> Moving :internal transition
    Moving --> Retracting :MoveDoneEvent
    Retracting --> Waiting: MoveDoneEvent

    Turning --> EStop :EStopEvent - All sub-states can go here.

    EStop --> Idle :ResetEvent
   