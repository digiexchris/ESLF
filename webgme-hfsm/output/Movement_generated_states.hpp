#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <string>

#include "deep_history_state.hpp"
#include "magic_enum.hpp"
#include "shallow_history_state.hpp"
#include "state_base.hpp"

#include "Movement_event_data.hpp"

// User Includes for the HFSM
//::::/g::::Includes::::


namespace Movement::Movement {

    typedef std::function<void(std::string_view)> LogCallback;

    enum class EventType {
      AtDestination,
      AutoNextPass,
      AutoReturnToStartPosition,
      EStop,
      MoveTo,
      NextPass,
      Reset,
      ResumeLastState,
      ReturnToStart,
      SetAutoMode,
      Start,
      StartMoving,
      Stop,
      WaitForUser,
    }; // ENUMS GENERATED FROM MODEL

    /**
     * @brief Class representing all events that this HFSM can respond
     * to / handle. Used as abstract interface for handleEvent().
     */
    class GeneratedEventBase : public EventBase {
    protected:
      EventType type;
    public:
      explicit GeneratedEventBase(const EventType& t) : type(t) {}
      virtual ~GeneratedEventBase() {}
      EventType get_type() const { return type; }
      virtual std::string to_string() const {
        return std::string(magic_enum::enum_name(type));
      }
    }; // Class GeneratedEventBase

    /**
     * @brief Class representing all events that this HFSM can respond
     * to / handle. Intended to be created / managed by the
     * EventFactory (below).
     */
    template <typename T>
    class Event : public GeneratedEventBase {
      T data;
    public:
      explicit Event(const EventType& t, const T& d) : GeneratedEventBase(t), data(d) {}
      virtual ~Event() {}
      T get_data() const { return data; }
    }; // Class Event

    // free the memory associated with the event
    static void consume_event(GeneratedEventBase *e) {
      delete e;
    }

    typedef Event<AtDestinationEventEventData> AtDestinationEventEvent;
    typedef Event<AutoNextPassEventData> AutoNextPassEventEvent;
    typedef Event<AutoReturnToStartPositionEventData> AutoReturnToStartPositionEvent;
    typedef Event<EStopEventEventData> EStopEventEvent;
    typedef Event<MoveToEventData> MoveToEventEvent;
    typedef Event<NextPassEventData> NextPassEventEvent;
    typedef Event<ResetEventData> ResetEventEvent;
    typedef Event<ResumeLastStateEventData> ResumeLastStateEventEvent;
    typedef Event<ReturnToStartEventData> ReturnToStartEventEvent;
    typedef Event<SetAutoModeEventData> SetAutoModeEvent;
    typedef Event<StartEventData> StartEventEvent;
    typedef Event<StartMovingEventData> StartMovingEventEvent;
    typedef Event<StopEventData> StopEventEvent;
    typedef Event<WaitForUserEventData> WaitForUserEventEvent;

    /**
     * @brief Class handling all Event creation, memory management, and
     *  ordering.
     */
    class EventFactory {
    public:
      ~EventFactory(void) { clear_events(); }

      void set_log_callback(LogCallback cb) {
        log_callback_ = cb;
      }

      void spawn_AtDestination_event(const AtDestinationEventEventData &data) {
        log("\033[32mSPAWN: AtDestinationEvent\033[0m");
        GeneratedEventBase *new_event = new AtDestinationEventEvent{EventType::AtDestination, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_AutoNextPassEvent_event(const AutoNextPassEventData &data) {
        log("\033[32mSPAWN: AutoNextPassEvent\033[0m");
        GeneratedEventBase *new_event = new AutoNextPassEventEvent{EventType::AutoNextPass, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_AutoReturnToStartPosition_event(const AutoReturnToStartPositionEventData &data) {
        log("\033[32mSPAWN: AutoReturnToStartPosition\033[0m");
        GeneratedEventBase *new_event = new AutoReturnToStartPositionEvent{EventType::AutoReturnToStartPosition, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_EStop_event(const EStopEventEventData &data) {
        log("\033[32mSPAWN: EStopEvent\033[0m");
        GeneratedEventBase *new_event = new EStopEventEvent{EventType::EStop, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_MoveToEvent_event(const MoveToEventData &data) {
        log("\033[32mSPAWN: MoveToEvent\033[0m");
        GeneratedEventBase *new_event = new MoveToEventEvent{EventType::MoveTo, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_NextPassEvent_event(const NextPassEventData &data) {
        log("\033[32mSPAWN: NextPassEvent\033[0m");
        GeneratedEventBase *new_event = new NextPassEventEvent{EventType::NextPass, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_Reset_event(const ResetEventData &data) {
        log("\033[32mSPAWN: ResetEvent\033[0m");
        GeneratedEventBase *new_event = new ResetEventEvent{EventType::Reset, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_ResumeLastState_event(const ResumeLastStateEventData &data) {
        log("\033[32mSPAWN: ResumeLastStateEvent\033[0m");
        GeneratedEventBase *new_event = new ResumeLastStateEventEvent{EventType::ResumeLastState, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_ReturnToStart_event(const ReturnToStartEventData &data) {
        log("\033[32mSPAWN: ReturnToStartEvent\033[0m");
        GeneratedEventBase *new_event = new ReturnToStartEventEvent{EventType::ReturnToStart, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_SetAutoMode_event(const SetAutoModeEventData &data) {
        log("\033[32mSPAWN: SetAutoMode\033[0m");
        GeneratedEventBase *new_event = new SetAutoModeEvent{EventType::SetAutoMode, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_Start_event(const StartEventData &data) {
        log("\033[32mSPAWN: StartEvent\033[0m");
        GeneratedEventBase *new_event = new StartEventEvent{EventType::Start, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_StartMoving_event(const StartMovingEventData &data) {
        log("\033[32mSPAWN: StartMovingEvent\033[0m");
        GeneratedEventBase *new_event = new StartMovingEventEvent{EventType::StartMoving, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_Stop_event(const StopEventData &data) {
        log("\033[32mSPAWN: StopEvent\033[0m");
        GeneratedEventBase *new_event = new StopEventEvent{EventType::Stop, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_WaitForUser_event(const WaitForUserEventData &data) {
        log("\033[32mSPAWN: WaitForUserEvent\033[0m");
        GeneratedEventBase *new_event = new WaitForUserEventEvent{EventType::WaitForUser, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }

      // Returns the number of events in the queue
      size_t get_num_events(void) {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        return events_.size();
      }

      // Blocks until an event is available
      void wait_for_events(void) {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (events_.size() > 0) {
          return;
        }
        queue_cv_.wait(lock);
      }

      // Blocks until an event is available or the timeout is reached
      void sleep_until_event(float seconds) {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (events_.size() > 0) {
          return;
        }
        queue_cv_.wait_for(lock, std::chrono::duration<float>(seconds));
      }

      // Blocks until an event is available
      GeneratedEventBase *get_next_event_blocking(void) {
        wait_for_events();
        std::unique_lock<std::mutex> lock(queue_mutex_);
        GeneratedEventBase *ptr = events_.front();
        events_.pop_front(); // remove the event from the Q
        return ptr;
      }

      // Retrieves the pointer to the next event in the queue, or
      // nullptr if it doesn't exist
      GeneratedEventBase *get_next_event(void) {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        GeneratedEventBase *ptr = nullptr;
        if (events_.size()) {
          ptr = events_.front();
          events_.pop_front(); // remove the event from the Q
        }
        return ptr;
      }

      // Clears the event queue and frees all event memory
      void clear_events(void) {
        // copy the queue so we can free the memory without holding the lock
        std::deque<GeneratedEventBase*> deq_copy;
        { std::lock_guard<std::mutex> lock(queue_mutex_);
          deq_copy = events_;
          events_.clear();
        }
        // make sure we don't hold the lock while freeing memory
        for (auto ptr : deq_copy) {
          consume_event(ptr);
        }
      }

      std::string to_string(void) {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        std::string qStr = "[ ";
        for (int i = 0; i < events_.size(); i++) {
          qStr += events_[i]->to_string();
        }
        qStr += " ]";
        return qStr;
      }

    protected:
      void log(std::string_view msg) {
        if (log_callback_) {
          log_callback_(msg);
        }
      }

      std::deque<GeneratedEventBase*> events_;
      std::mutex queue_mutex_;
      std::condition_variable queue_cv_;
      LogCallback log_callback_{nullptr};
    }; // class EventFactory

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
      void spawn_AtDestinationEvent_event(const AtDestinationEventEventData &data) { event_factory.spawn_AtDestination_event(data); }
      void spawn_AutoNextPassEvent_event(const AutoNextPassEventData &data) { event_factory.spawn_AutoNextPassEvent_event(data); }
      void spawn_AutoReturnToStartPosition_event(const AutoReturnToStartPositionEventData &data) { event_factory.spawn_AutoReturnToStartPosition_event(data); }
      void spawn_EStopEvent_event(const EStopEventEventData &data) { event_factory.spawn_EStop_event(data); }
      void spawn_MoveToEvent_event(const MoveToEventData &data) { event_factory.spawn_MoveToEvent_event(data); }
      void spawn_NextPassEvent_event(const NextPassEventData &data) { event_factory.spawn_NextPassEvent_event(data); }
      void spawn_ResetEvent_event(const ResetEventData &data) { event_factory.spawn_Reset_event(data); }
      void spawn_ResumeLastStateEvent_event(const ResumeLastStateEventData &data) { event_factory.spawn_ResumeLastState_event(data); }
      void spawn_ReturnToStartEvent_event(const ReturnToStartEventData &data) { event_factory.spawn_ReturnToStart_event(data); }
      void spawn_SetAutoMode_event(const SetAutoModeEventData &data) { event_factory.spawn_SetAutoMode_event(data); }
      void spawn_StartEvent_event(const StartEventData &data) { event_factory.spawn_Start_event(data); }
      void spawn_StartMovingEvent_event(const StartMovingEventData &data) { event_factory.spawn_StartMoving_event(data); }
      void spawn_StopEvent_event(const StopEventData &data) { event_factory.spawn_Stop_event(data); }
      void spawn_WaitForUserEvent_event(const WaitForUserEventData &data) { event_factory.spawn_WaitForUser_event(data); }

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
      ~Root(void) {}

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
        ~ManualMove ( void ) {}
      
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
        ~Turning ( void ) {}
      
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
          ~Running ( void ) {}
        
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
            ~WaitingForUser ( void ) {}
          
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
            ~WaitForSync ( void ) {}
          
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
            ~Moving ( void ) {}
          
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
            ~AtDestination ( void ) {}
          
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
            ~ReturningToStartPosition ( void ) {}
          
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
          ~Stopped ( void ) {}
        
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
        ~EStop ( void ) {}
      
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
