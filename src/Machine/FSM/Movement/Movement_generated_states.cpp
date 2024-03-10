#include "Movement_generated_states.hpp"

using namespace Movement::Movement;

// User Definitions for the HFSM
//::::/g::::Definitions::::


/* * *  Definitions for Root : /g  * * */
// Generated Definitions for the root state
void Root::initialize(void) {
  // Run the model's Initialization code
  log("\033[36mMovement:/g HFSM Initialization\033[0m");
  //::::/g::::Initialization::::
  
  // now set the states up properly
  // External Transition : Action for: /g/3
  _root->log("\033[36mTRANSITION::ACTION for /g/3\033[0m");
  
  //::::/g/3::::Action::::
  
  // State : entry for: /g/o
  _root->MOVEMENT_OBJ__TURNING_OBJ.entry();
  
  // initialize our new active state
  _root->MOVEMENT_OBJ__TURNING_OBJ.initialize();
};

void Root::handle_all_events(void) {
  GeneratedEventBase* e;
  // get the next event and check if it's nullptr
  while ((e = event_factory.get_next_event())) {
    [[maybe_unused]] bool did_handle = handleEvent( e );
    log("\033[0mHANDLED " +
        e->to_string() +
        (did_handle ? ": \033[32mtrue" : ": \033[31mfalse") +
        "\033[0m");
    // free the memory that was allocated when it was spawned
    consume_event( e );
  }
}

void Root::terminate(void) {
  // will call exit() and exitChildren() on _activeState if it
  // exists
  exitChildren();
};

void Root::restart(void) {
  terminate();
  initialize();
};

bool Root::has_stopped(void) {
  bool reachedEnd = false;
  return reachedEnd;
};

bool Root::handleEvent(GeneratedEventBase *event) {
  bool handled = false;

  // Get the currently active leaf state
  StateBase *activeLeaf = getActiveLeaf();

  if (activeLeaf != nullptr && activeLeaf != this) {
    // have the active leaf handle the event, this will bubble up until
    // the event is handled or it reaches the root.
    handled = activeLeaf->handleEvent(event);
  }

  return handled;
}

/* * *  Definitions for ManualMove : /g/Q  * * */

// User Definitions for the HFSM
//::::/g/Q::::Definitions::::


void Root::ManualMove::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::ManualMove::entry ( void ) {
  _root->log("\033[36mENTRY::ManualMove::/g/Q\033[0m");
  // Entry action for this state
  //::::/g/Q::::Entry::::
  
}

void Root::ManualMove::exit ( void ) {
  _root->log("\033[36mEXIT::ManualMove::/g/Q\033[0m");
  // Call the Exit Action for this state
  //::::/g/Q::::Exit::::
  
}

void Root::ManualMove::tick ( void ) {
  _root->log("\033[36mTICK::ManualMove::/g/Q\033[0m");
  // Call the Tick Action for this state
  //::::/g/Q::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::ManualMove::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::ManualMove::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::EStop:
  case EventType::MoveTo:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ReturnToStart:
  case EventType::SetAutoMode:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::Stop:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::ResumeLastState:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/X\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__MANUALMOVE_OBJ.exitChildren();
      // State : exit for: /g/Q
      _root->MOVEMENT_OBJ__MANUALMOVE_OBJ.exit();
      // External Transition : Action for: /g/X
      _root->log("\033[36mTRANSITION::ACTION for /g/X\033[0m");
      
      //::::/g/X::::Action::::
      
      _root->log("\033[31mSTATE TRANSITION: ManualMove->ResumeLastState\033[0m");
      
        // going into deep history pseudo-state
        //TODO this doesn't coimpile_root->MOVEMENT_OBJ.setDeepHistory();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  // can't buble up, we are a root state.
  return handled;
}
/* * *  Definitions for Turning : /g/o  * * */

// User Definitions for the HFSM
//::::/g/o::::Definitions::::


void Root::Turning::initialize ( void ) {
  // External Transition : Action for: /g/o/X
  _root->log("\033[36mTRANSITION::ACTION for /g/o/X\033[0m");
  
  //::::/g/o/X::::Action::::
  
  // State : entry for: /g/o/b
  _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.entry();
  
  // initialize our new active state
  _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.initialize();
}

void Root::Turning::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::/g/o\033[0m");
  // Entry action for this state
  //::::/g/o::::Entry::::
  
}

void Root::Turning::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::/g/o\033[0m");
  // Call the Exit Action for this state
  //::::/g/o::::Exit::::
  
}

void Root::Turning::tick ( void ) {
  _root->log("\033[36mTICK::Turning::/g/o\033[0m");
  // Call the Tick Action for this state
  //::::/g/o::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::Stop:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  case EventType::SetAutoMode:
    if ( false ) {  // makes generation easier :)
    }
    else if (true) {
      _root->log("\033[37mNO GUARD on INTERNAL TRANSITION:/g/o/U\033[0m");
      // run transition action
      //::::/g/o/U::::Action::::
      
      // make sure nothing else handles this event
      handled = true;
    }
    break;
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::MoveTo:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/6\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ.exitChildren();
      // State : exit for: /g/o
      _root->MOVEMENT_OBJ__TURNING_OBJ.exit();
      // External Transition : Action for: /g/6
      _root->log("\033[36mTRANSITION::ACTION for /g/6\033[0m");
      
      //::::/g/6::::Action::::
      
      // State : entry for: /g/Q
      _root->MOVEMENT_OBJ__MANUALMOVE_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning->ManualMove\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__MANUALMOVE_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    case EventType::EStop:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/Y\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ.exitChildren();
      // State : exit for: /g/o
      _root->MOVEMENT_OBJ__TURNING_OBJ.exit();
      // External Transition : Action for: /g/Y
      _root->log("\033[36mTRANSITION::ACTION for /g/Y\033[0m");
      
      //::::/g/Y::::Action::::
      
      // State : entry for: /g/M
      _root->MOVEMENT_OBJ__ESTOP_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning->EStop\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__ESTOP_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  // can't buble up, we are a root state.
  return handled;
}
/* * *  Definitions for Turning::Running : /g/o/4  * * */

// User Definitions for the HFSM
//::::/g/o/4::::Definitions::::


void Root::Turning::Running::initialize ( void ) {
  // External Transition : Action for: /g/o/4/H
  _root->log("\033[36mTRANSITION::ACTION for /g/o/4/H\033[0m");
  
  //::::/g/o/4/H::::Action::::
  
  // State : entry for: /g/o/4/i
  _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.entry();
  
  // initialize our new active state
  _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.initialize();
}

void Root::Turning::Running::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::/g/o/4\033[0m");
  // Entry action for this state
  //::::/g/o/4::::Entry::::
  
}

void Root::Turning::Running::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::/g/o/4\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4::::Exit::::
  
}

void Root::Turning::Running::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::/g/o/4\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4::::Tick::::
      //   Update();
      // GenerateMoves();
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::Stop:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/p\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ.exitChildren();
      // State : exit for: /g/o/4
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ.exit();
      // External Transition : Action for: /g/o/p
      _root->log("\033[36mTRANSITION::ACTION for /g/o/p\033[0m");
      
      //::::/g/o/p::::Action::::
      
      // State : entry for: /g/o/b
      _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running->Turning::Stopped\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Running::WaitingForUser : /g/o/4/i  * * */

// User Definitions for the HFSM
//::::/g/o/4/i::::Definitions::::


void Root::Turning::Running::WaitingForUser::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Running::WaitingForUser::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::WaitingForUser::/g/o/4/i\033[0m");
  // Entry action for this state
  //::::/g/o/4/i::::Entry::::
  
}

void Root::Turning::Running::WaitingForUser::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::WaitingForUser::/g/o/4/i\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4/i::::Exit::::
  
}

void Root::Turning::Running::WaitingForUser::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::WaitingForUser::/g/o/4/i\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4/i::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::WaitingForUser::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::WaitingForUser::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::NextPass:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/a\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.exitChildren();
      // State : exit for: /g/o/4/i
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.exit();
      // External Transition : Action for: /g/o/4/a
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/a\033[0m");
      
      //::::/g/o/4/a::::Action::::
      
      // State : entry for: /g/o/4/E
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::WaitingForUser->Turning::Running::WaitForSync\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    case EventType::ReturnToStart:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/s\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.exitChildren();
      // State : exit for: /g/o/4/i
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.exit();
      // External Transition : Action for: /g/o/4/s
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/s\033[0m");
      
      //::::/g/o/4/s::::Action::::
      
      // State : entry for: /g/o/4/Z
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::WaitingForUser->Turning::Running::ReturningToStartPosition\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Running::WaitForSync : /g/o/4/E  * * */

// User Definitions for the HFSM
//::::/g/o/4/E::::Definitions::::


void Root::Turning::Running::WaitForSync::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Running::WaitForSync::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::WaitForSync::/g/o/4/E\033[0m");
  // Entry action for this state
  //::::/g/o/4/E::::Entry::::
  
}

void Root::Turning::Running::WaitForSync::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::WaitForSync::/g/o/4/E\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4/E::::Exit::::
  
}

void Root::Turning::Running::WaitForSync::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::WaitForSync::/g/o/4/E\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4/E::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::WaitForSync::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::WaitForSync::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::StartMoving:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/A\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.exitChildren();
      // State : exit for: /g/o/4/E
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.exit();
      // External Transition : Action for: /g/o/4/A
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/A\033[0m");
      
      //::::/g/o/4/A::::Action::::
      
      // State : entry for: /g/o/4/D
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::WaitForSync->Turning::Running::Moving\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Running::Moving : /g/o/4/D  * * */

// User Definitions for the HFSM
//::::/g/o/4/D::::Definitions::::


void Root::Turning::Running::Moving::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Running::Moving::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::Moving::/g/o/4/D\033[0m");
  // Entry action for this state
  //::::/g/o/4/D::::Entry::::
  
}

void Root::Turning::Running::Moving::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::Moving::/g/o/4/D\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4/D::::Exit::::
  
}

void Root::Turning::Running::Moving::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::Moving::/g/o/4/D\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4/D::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::Moving::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::Moving::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::AtDestination:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/0\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ.exitChildren();
      // State : exit for: /g/o/4/D
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ.exit();
      // External Transition : Action for: /g/o/4/0
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/0\033[0m");
      
      //::::/g/o/4/0::::Action::::
      
      // State : entry for: /g/o/4/O
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::Moving->Turning::Running::AtDestination\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Running::AtDestination : /g/o/4/O  * * */

// User Definitions for the HFSM
//::::/g/o/4/O::::Definitions::::


void Root::Turning::Running::AtDestination::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Running::AtDestination::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::AtDestination::/g/o/4/O\033[0m");
  // Entry action for this state
  //::::/g/o/4/O::::Entry::::
  
}

void Root::Turning::Running::AtDestination::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::AtDestination::/g/o/4/O\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4/O::::Exit::::
  
}

void Root::Turning::Running::AtDestination::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::AtDestination::/g/o/4/O\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4/O::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::AtDestination::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::AtDestination::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::StartMoving:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::WaitForUser:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/Nw\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.exitChildren();
      // State : exit for: /g/o/4/O
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.exit();
      // External Transition : Action for: /g/o/4/Nw
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/Nw\033[0m");
      
      //::::/g/o/4/Nw::::Action::::
      
      // State : entry for: /g/o/4/i
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::AtDestination->Turning::Running::WaitingForUser\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    case EventType::AutoReturnToStartPosition:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/W\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.exitChildren();
      // State : exit for: /g/o/4/O
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ.exit();
      // External Transition : Action for: /g/o/4/W
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/W\033[0m");
      
      //::::/g/o/4/W::::Action::::
      
      // State : entry for: /g/o/4/Z
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::AtDestination->Turning::Running::ReturningToStartPosition\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Running::ReturningToStartPosition : /g/o/4/Z  * * */

// User Definitions for the HFSM
//::::/g/o/4/Z::::Definitions::::


void Root::Turning::Running::ReturningToStartPosition::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Running::ReturningToStartPosition::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Running::ReturningToStartPosition::/g/o/4/Z\033[0m");
  // Entry action for this state
  //::::/g/o/4/Z::::Entry::::
  // if(myPosition != myStartPosition)
  // {
  //   ReturnToStart();
  // }
}

void Root::Turning::Running::ReturningToStartPosition::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Running::ReturningToStartPosition::/g/o/4/Z\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/4/Z::::Exit::::
  
}

void Root::Turning::Running::ReturningToStartPosition::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Running::ReturningToStartPosition::/g/o/4/Z\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/4/Z::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Running::ReturningToStartPosition::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Running::ReturningToStartPosition::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::Start:
  case EventType::StartMoving:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::WaitForUser:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/M\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.exitChildren();
      // State : exit for: /g/o/4/Z
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.exit();
      // External Transition : Action for: /g/o/4/M
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/M\033[0m");
      
      //::::/g/o/4/M::::Action::::
      
      // State : entry for: /g/o/4/i
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::ReturningToStartPosition->Turning::Running::WaitingForUser\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    case EventType::AutoNextPass:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/4/g\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.exitChildren();
      // State : exit for: /g/o/4/Z
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ.exit();
      // External Transition : Action for: /g/o/4/g
      _root->log("\033[36mTRANSITION::ACTION for /g/o/4/g\033[0m");
      
      //::::/g/o/4/g::::Action::::
      
      // State : entry for: /g/o/4/E
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Running::ReturningToStartPosition->Turning::Running::WaitForSync\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for Turning::Stopped : /g/o/b  * * */

// User Definitions for the HFSM
//::::/g/o/b::::Definitions::::


void Root::Turning::Stopped::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::Turning::Stopped::entry ( void ) {
  _root->log("\033[36mENTRY::Turning::Stopped::/g/o/b\033[0m");
  // Entry action for this state
  //::::/g/o/b::::Entry::::
  
}

void Root::Turning::Stopped::exit ( void ) {
  _root->log("\033[36mEXIT::Turning::Stopped::/g/o/b\033[0m");
  // Call the Exit Action for this state
  //::::/g/o/b::::Exit::::
  
}

void Root::Turning::Stopped::tick ( void ) {
  _root->log("\033[36mTICK::Turning::Stopped::/g/o/b\033[0m");
  // Call the Tick Action for this state
  //::::/g/o/b::::Tick::::
        // Update();
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::Turning::Stopped::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::Turning::Stopped::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::NextPass:
  case EventType::Reset:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::StartMoving:
  case EventType::Stop:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::Start:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/o/P\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.exitChildren();
      // State : exit for: /g/o/b
      _root->MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ.exit();
      // External Transition : Action for: /g/o/P
      _root->log("\033[36mTRANSITION::ACTION for /g/o/P\033[0m");
      
      //::::/g/o/P::::Action::::
      
      // State : entry for: /g/o/4
      _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ.entry();
      _root->log("\033[31mSTATE TRANSITION: Turning::Stopped->Turning::Running\033[0m");
      
        // going into regular state
        _root->MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ.initialize();
        // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  if (!handled) {
    // now check parent states
    handled = _parentState->handleEvent( event );
  }
  return handled;
}
/* * *  Definitions for EStop : /g/M  * * */

// User Definitions for the HFSM
//::::/g/M::::Definitions::::


void Root::EStop::initialize ( void ) {
  // if we're a leaf state, make sure we're active
  makeActive();
}

void Root::EStop::entry ( void ) {
  _root->log("\033[36mENTRY::EStop::/g/M\033[0m");
  // Entry action for this state
  //::::/g/M::::Entry::::
  
}

void Root::EStop::exit ( void ) {
  _root->log("\033[36mEXIT::EStop::/g/M\033[0m");
  // Call the Exit Action for this state
  //::::/g/M::::Exit::::
  
}

void Root::EStop::tick ( void ) {
  _root->log("\033[36mTICK::EStop::/g/M\033[0m");
  // Call the Tick Action for this state
  //::::/g/M::::Tick::::
  
  if ( _activeState != nullptr && _activeState != this )
    _activeState->tick();
}

double Root::EStop::getTimerPeriod ( void ) {
  return (double)(1);
}

bool Root::EStop::handleEvent ( GeneratedEventBase* event ) {
  bool handled = false;

  // take care of all event types that this branch will not handle -
  // for more consistent run-time performnace
  switch ( event->get_type() ) {
  case EventType::AtDestination:
  case EventType::AutoNextPass:
  case EventType::AutoReturnToStartPosition:
  case EventType::EStop:
  case EventType::MoveTo:
  case EventType::NextPass:
  case EventType::ResumeLastState:
  case EventType::ReturnToStart:
  case EventType::SetAutoMode:
  case EventType::Start:
  case EventType::StartMoving:
  case EventType::Stop:
  case EventType::WaitForUser:
    handled = true;
    break;
  default:
    handled = false;
    break;
  }

  if (handled) {
    // we didn't actually handle the event, but return anyway
    return false;
  }

  // handle internal transitions first
  switch ( event->get_type() ) {
  default:
    handled = false;
    break;
  }
  if (!handled) {
    // handle external transitions here
    switch ( event->get_type() ) {
    case EventType::Reset:
      if ( false ) { }  // makes generation easier :)
      else if ( true ) {
        _root->log("\033[37mNO GUARD on EXTERNAL TRANSITION:/g/G\033[0m");
        // Transitioning states!
        // Call all from prev state down exits
      _root->MOVEMENT_OBJ__ESTOP_OBJ.exitChildren();
      // State : exit for: /g/M
      _root->MOVEMENT_OBJ__ESTOP_OBJ.exit();
      // External Transition : Action for: /g/G
      _root->log("\033[36mTRANSITION::ACTION for /g/G\033[0m");
      
      //::::/g/G::::Action::::
      
      _root->log("\033[31mSTATE TRANSITION: EStop->ResumeLastMode\033[0m");
      
        // going into shallow history pseudo-state
        //TODO this doesn't compile_root->MOVEMENT_OBJ.setShallowHistory();
          // make sure nothing else handles this event
        handled = true;
        }
      break;
    default:
      handled = false;
      break;
    }
  }
  // can't buble up, we are a root state.
  return handled;
}
