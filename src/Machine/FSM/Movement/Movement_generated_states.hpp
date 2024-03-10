#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <string>

#include "Logging/Logger.hpp"
#include "Machine/FSM/Movement/EventFactory.hpp"
#include "deep_history_state.hpp"
#include "magic_enum.hpp"
#include "shallow_history_state.hpp"
#include "state_base.hpp"

#include "Movement_event_data.hpp"

// User Includes for the HFSM
//::::/g::::Includes::::


namespace Movement::Movement {

    
    /**
     * @brief The ROOT of the HFSM - contains the declarations from
     *  the user as well as the entire substate tree.
     */
    class Root : public StateBase {
    public:
      // User Declarations for the HFSM
      //::::/g::::Declarations::::
      

    protected:
      void log(const std::string& msg) {
        if (log_callback_) {
          log_callback_(msg);
        }
      }

      LogCallback log_callback_{nullptr};

    public:
      // event factory for spawning / ordering events
      EventFactory event_factory;

      void set_log_callback(LogCallback cb) {
        log_callback_ = cb;
        event_factory.set_log_callback(cb);
      }

      // helper functions for spawning events into the HFSM
      void spawn_AtDestination_event(const AtDestinationEventData &data) { event_factory.spawn_AtDestination_event(data); }
      void spawn_AutoNextPass_event(const AutoNextPassEventData &data) { event_factory.spawn_AutoNextPass_event(data); }
      void spawn_AutoReturnToStartPosition_event(const AutoReturnToStartPositionEventData &data) { event_factory.spawn_AutoReturnToStartPosition_event(data); }
      void spawn_EStop_event(const EStopEventData &data) { event_factory.spawn_EStop_event(data); }
      void spawn_MoveTo_event(const MoveToEventData &data) { event_factory.spawn_MoveTo_event(data); }
      void spawn_NextPass_event(const NextPassEventData &data) { event_factory.spawn_NextPass_event(data); }
      void spawn_Reset_event(const ResetEventData &data) { event_factory.spawn_Reset_event(data); }
      void spawn_ResumeLastState_event(const ResumeLastStateEventData &data) { event_factory.spawn_ResumeLastState_event(data); }
      void spawn_ReturnToStart_event(const ReturnToStartEventData &data) { event_factory.spawn_ReturnToStart_event(data); }
      void spawn_SetAutoMode_event(const SetAutoModeEventData &data) { event_factory.spawn_SetAutoMode_event(data); }
      void spawn_StartRunning_event(const StartRunningEventData &data) { event_factory.spawn_Start_event(data); }
      void spawn_StartMoving_event(const StartMovingEventData &data) { event_factory.spawn_StartMoving_event(data); }
      void spawn_Stop_event(const StopEventData &data) { event_factory.spawn_Stop_event(data); }
      void spawn_WaitForUser_event(const WaitForUserEventData &data) { event_factory.spawn_WaitForUser_event(data); }

      // Constructors
      Root() : StateBase(),
      MOVEMENT_OBJ__MANUALMOVE_OBJ ( this, this ),
            MOVEMENT_OBJ__RESUMELASTSTATE_OBJ ( this ),
                  MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ),
                        MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ),
                        MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ),
                        MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ),
                        MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ),
                        MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ ),
                  MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ ( this, &MOVEMENT_OBJ__TURNING_OBJ ),
                  MOVEMENT_OBJ__TURNING_OBJ ( this, this ),
            MOVEMENT_OBJ__ESTOP_OBJ ( this, this ),
            MOVEMENT_OBJ__RESUMELASTMODE_OBJ ( this ),
      _root(this)
      {}
      ~Root(void) = default;

      /**
       * @brief Fully initializes the HFSM. Runs the HFSM Initialization
       *  code from the model, then sets the inital state and runs the
       *  initial transition and entry actions accordingly.
       */
      void initialize(void);

      /**
       * @brief Returns true if there are any events in the event queue.
       */
      bool has_events(void) {
        return event_factory.get_num_events() > 0;
      }

      /**
       * @brief Sleeps until an event is available or the current state's timer
       *  period expires, then returns. This will block until an event is
       *  available. The amount of time spent sleeping is determined by the
       *  current state's timer period.
       */
      void sleep_until_event(void) {
        event_factory.sleep_until_event(getActiveLeaf()->getTimerPeriod());
      }

      /**
       * @brief Waits for an event to be available, then returns.
       * This will block until an event is available.
       */
      void wait_for_events(void) {
        event_factory.wait_for_events();
      }

      /**
       * @brief Handles all events in the event queue, ensuring to free the
       * memory. This will ensure that any events spawned from other event
       * transitions / actions are handled. Returns once there are no more
       * events in the queue to process.
       */
      void handle_all_events(void);

      /**
       * @brief Terminates the HFSM, calling exit functions for the
       *  active leaf state upwards through its parents all the way to
       *  the root.
       */
      void terminate(void);

      /**
       * @brief Restarts the HFSM by calling terminate and then
       *  initialize.
       */
      void restart(void);

      /**
       * @brief Returns true if the HFSM has reached its END State
       */
      bool has_stopped(void);

      /**
       * @brief Calls handleEvent on the activeLeaf.
       *
       * @param[in] EventBase* Event needing to be handled
       *
       * @return true if event is consumed, false otherwise
       */
      bool handleEvent(EventBase * event) {
        return handleEvent( static_cast<GeneratedEventBase*>(event) );
      }

      /**
       * @brief Calls handleEvent on the activeLeaf.
       *
       * @param[in] EventBase* Event needing to be handled
       *
       * @return true if event is consumed, false otherwise
       */
      bool handleEvent(GeneratedEventBase * event);

      // Child Substates
      // Declaration for ManualMove : /g/Q
      class ManualMove : public StateBase {
      public:
        // User Declarations for the State
        //::::/g/Q::::Declarations::::
        
      
      public:
        // Pointer to the root of the HFSM.
        Root *_root;
      
        // Constructors
        ManualMove  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
        ~ManualMove ( void ) = default;
      
        // StateBase Interface
        void   initialize ( void );
        void   entry ( void );
        void   exit ( void );
        void   tick ( void );
        double getTimerPeriod ( void );
        virtual bool   handleEvent ( EventBase* event ) {
          return handleEvent( static_cast<GeneratedEventBase*>(event) );
        }
        virtual bool   handleEvent ( GeneratedEventBase* event );
      
      };
      // Declaration for Turning : /g/o
      class Turning : public StateBase {
      public:
        // User Declarations for the State
        //::::/g/o::::Declarations::::
        
      
      public:
        // Pointer to the root of the HFSM.
        Root *_root;
      
        // Constructors
        Turning  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
        ~Turning ( void ) = default;
      
        // StateBase Interface
        void   initialize ( void );
        void   entry ( void );
        void   exit ( void );
        void   tick ( void );
        double getTimerPeriod ( void );
        virtual bool   handleEvent ( EventBase* event ) {
          return handleEvent( static_cast<GeneratedEventBase*>(event) );
        }
        virtual bool   handleEvent ( GeneratedEventBase* event );
      
        // Declaration for Turning::Running : /g/o/4
        class Running : public StateBase {
        public:
          // User Declarations for the State
          //::::/g/o/4::::Declarations::::
          bool myIsAutoMode = false;
        
        public:
          // Pointer to the root of the HFSM.
          Root *_root;
        
          // Constructors
          Running  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
          ~Running ( void ) = default;
        
          // StateBase Interface
          void   initialize ( void );
          void   entry ( void );
          void   exit ( void );
          void   tick ( void );
          double getTimerPeriod ( void );
          virtual bool   handleEvent ( EventBase* event ) {
            return handleEvent( static_cast<GeneratedEventBase*>(event) );
          }
          virtual bool   handleEvent ( GeneratedEventBase* event );
        
          // Declaration for Turning::Running::WaitingForUser : /g/o/4/i
          class WaitingForUser : public StateBase {
          public:
            // User Declarations for the State
            //::::/g/o/4/i::::Declarations::::
            
          
          public:
            // Pointer to the root of the HFSM.
            Root *_root;
          
            // Constructors
            WaitingForUser  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
            ~WaitingForUser ( void ) = default;
          
            // StateBase Interface
            void   initialize ( void );
            void   entry ( void );
            void   exit ( void );
            void   tick ( void );
            double getTimerPeriod ( void );
            virtual bool   handleEvent ( EventBase* event ) {
              return handleEvent( static_cast<GeneratedEventBase*>(event) );
            }
            virtual bool   handleEvent ( GeneratedEventBase* event );
          
          };
          // Declaration for Turning::Running::WaitForSync : /g/o/4/E
          class WaitForSync : public StateBase {
          public:
            // User Declarations for the State
            //::::/g/o/4/E::::Declarations::::
            
          
          public:
            // Pointer to the root of the HFSM.
            Root *_root;
          
            // Constructors
            WaitForSync  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
            ~WaitForSync ( void ) = default;
          
            // StateBase Interface
            void   initialize ( void );
            void   entry ( void );
            void   exit ( void );
            void   tick ( void );
            double getTimerPeriod ( void );
            virtual bool   handleEvent ( EventBase* event ) {
              return handleEvent( static_cast<GeneratedEventBase*>(event) );
            }
            virtual bool   handleEvent ( GeneratedEventBase* event );
          
          };
          // Declaration for Turning::Running::Moving : /g/o/4/D
          class Moving : public StateBase {
          public:
            // User Declarations for the State
            //::::/g/o/4/D::::Declarations::::
            
          
          public:
            // Pointer to the root of the HFSM.
            Root *_root;
          
            // Constructors
            Moving  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
            ~Moving ( void ) = default;
          
            // StateBase Interface
            void   initialize ( void );
            void   entry ( void );
            void   exit ( void );
            void   tick ( void );
            double getTimerPeriod ( void );
            virtual bool   handleEvent ( EventBase* event ) {
              return handleEvent( static_cast<GeneratedEventBase*>(event) );
            }
            virtual bool   handleEvent ( GeneratedEventBase* event );
          
          };
          // Declaration for Turning::Running::AtDestination : /g/o/4/O
          class AtDestination : public StateBase {
          public:
            // User Declarations for the State
            //::::/g/o/4/O::::Declarations::::
            
          
          public:
            // Pointer to the root of the HFSM.
            Root *_root;
          
            // Constructors
            AtDestination  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
            ~AtDestination ( void ) = default;
          
            // StateBase Interface
            void   initialize ( void );
            void   entry ( void );
            void   exit ( void );
            void   tick ( void );
            double getTimerPeriod ( void );
            virtual bool   handleEvent ( EventBase* event ) {
              return handleEvent( static_cast<GeneratedEventBase*>(event) );
            }
            virtual bool   handleEvent ( GeneratedEventBase* event );
          
          };
          // Declaration for Turning::Running::ReturningToStartPosition : /g/o/4/Z
          class ReturningToStartPosition : public StateBase {
          public:
            // User Declarations for the State
            //::::/g/o/4/Z::::Declarations::::
            
          
          public:
            // Pointer to the root of the HFSM.
            Root *_root;
          
            // Constructors
            ReturningToStartPosition  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
            ~ReturningToStartPosition ( void ) = default;
          
            // StateBase Interface
            void   initialize ( void );
            void   entry ( void );
            void   exit ( void );
            void   tick ( void );
            double getTimerPeriod ( void );
            virtual bool   handleEvent ( EventBase* event ) {
              return handleEvent( static_cast<GeneratedEventBase*>(event) );
            }
            virtual bool   handleEvent ( GeneratedEventBase* event );
          
          };
        };
        // Declaration for Turning::Stopped : /g/o/b
        class Stopped : public StateBase {
        public:
          // User Declarations for the State
          //::::/g/o/b::::Declarations::::
          
        
        public:
          // Pointer to the root of the HFSM.
          Root *_root;
        
          // Constructors
          Stopped  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
          ~Stopped ( void ) = default;
        
          // StateBase Interface
          void   initialize ( void );
          void   entry ( void );
          void   exit ( void );
          void   tick ( void );
          double getTimerPeriod ( void );
          virtual bool   handleEvent ( EventBase* event ) {
            return handleEvent( static_cast<GeneratedEventBase*>(event) );
          }
          virtual bool   handleEvent ( GeneratedEventBase* event );
        
        };
      };
      // Declaration for EStop : /g/M
      class EStop : public StateBase {
      public:
        // User Declarations for the State
        //::::/g/M::::Declarations::::
        
      
      public:
        // Pointer to the root of the HFSM.
        Root *_root;
      
        // Constructors
        EStop  ( Root* root, StateBase* parent ) : StateBase(parent), _root(root) {}
        ~EStop ( void ) = default;
      
        // StateBase Interface
        void   initialize ( void );
        void   entry ( void );
        void   exit ( void );
        void   tick ( void );
        double getTimerPeriod ( void );
        virtual bool   handleEvent ( EventBase* event ) {
          return handleEvent( static_cast<GeneratedEventBase*>(event) );
        }
        virtual bool   handleEvent ( GeneratedEventBase* event );
      
      };

      // END STATE

      // State Objects
      ManualMove MOVEMENT_OBJ__MANUALMOVE_OBJ;
      DeepHistoryState MOVEMENT_OBJ__RESUMELASTSTATE_OBJ;
      Turning::Running::WaitingForUser MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITINGFORUSER_OBJ;
      Turning::Running::WaitForSync MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__WAITFORSYNC_OBJ;
      Turning::Running::Moving MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__MOVING_OBJ;
      Turning::Running::AtDestination MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__ATDESTINATION_OBJ;
      Turning::Running::ReturningToStartPosition MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ__RETURNINGTOSTARTPOSITION_OBJ;
      Turning::Running MOVEMENT_OBJ__TURNING_OBJ__RUNNING_OBJ;
      Turning::Stopped MOVEMENT_OBJ__TURNING_OBJ__STOPPED_OBJ;
      Turning MOVEMENT_OBJ__TURNING_OBJ;
      EStop MOVEMENT_OBJ__ESTOP_OBJ;
      ShallowHistoryState MOVEMENT_OBJ__RESUMELASTMODE_OBJ;
      // Keep a _root for easier templating, it will point to us
      Root *_root;
    }; // class Root

}; // namespace Movement::Movement
