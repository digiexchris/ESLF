#pragma once
#include "Machine/FSM/Movement/Events.hpp"
#include "Movement_event_data.hpp"
#include "state_base.hpp"
#include "magic_enum.hpp"
#include "Logging/Logger.hpp"

#include "EventTypes.hpp"
#include "EventBase.hpp"
#include <deque>

namespace Movement::Movement {

/**
     * @brief Class handling all Event creation, memory management, and
     *  ordering.
     */


    class EventFactory {
    public:
      ~EventFactory(void) noexcept { clear_events(); }

      void set_log_callback(LogCallback cb) {
        log_callback_ = cb;
      }

      void spawn_AtDestination_event(const AtDestinationEventData &data) {
        log("\033[32mSPAWN: AtDestinationEvent\033[0m");
        GeneratedEventBase *new_event = new AtDestinationEvent{EventType::AtDestination, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_AutoNextPass_event(const AutoNextPassEventData &data) {
        log("\033[32mSPAWN: AutoNextPassEvent\033[0m");
        GeneratedEventBase *new_event = new AutoNextPassEvent{EventType::AutoNextPass, data};
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
      void spawn_EStop_event(const EStopEventData &data) {
        log("\033[32mSPAWN: EStopEvent\033[0m");
        GeneratedEventBase *new_event = new EStopEvent{EventType::EStop, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_MoveTo_event(const MoveToEventData &data) {
        log("\033[32mSPAWN: MoveToEvent\033[0m");
        GeneratedEventBase *new_event = new MoveToEvent{EventType::MoveTo, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_NextPass_event(const NextPassEventData &data) {
        log("\033[32mSPAWN: NextPassEvent\033[0m");
        GeneratedEventBase *new_event = new NextPassEvent{EventType::NextPass, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_Reset_event(const ResetEventData &data) {
        log("\033[32mSPAWN: ResetEvent\033[0m");
        GeneratedEventBase *new_event = new ResetEvent{EventType::Reset, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_ResumeLastState_event(const ResumeLastStateEventData &data) {
        log("\033[32mSPAWN: ResumeLastStateEvent\033[0m");
        GeneratedEventBase *new_event = new ResumeLastStateEvent{EventType::ResumeLastState, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_ReturnToStart_event(const ReturnToStartEventData &data) {
        log("\033[32mSPAWN: ReturnToStartEvent\033[0m");
        GeneratedEventBase *new_event = new ReturnToStartEvent{EventType::ReturnToStart, data};
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
      void spawn_Start_event(const StartRunningEventData &data) {
        log("\033[32mSPAWN: StartEvent\033[0m");
        GeneratedEventBase *new_event = new StartRunningEvent{EventType::Start, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_StartMoving_event(const StartMovingEventData &data) {
        log("\033[32mSPAWN: StartMovingEvent\033[0m");
        GeneratedEventBase *new_event = new StartMovingEvent{EventType::StartMoving, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_Stop_event(const StopEventData &data) {
        log("\033[32mSPAWN: StopEvent\033[0m");
        GeneratedEventBase *new_event = new StopEvent{EventType::Stop, data};
        std::lock_guard<std::mutex> lock(queue_mutex_);
        events_.push_back(new_event);
        queue_cv_.notify_one();
      }
      void spawn_WaitForUser_event(const WaitForUserEventData &data) {
        log("\033[32mSPAWN: WaitForUserEvent\033[0m");
        GeneratedEventBase *new_event = new WaitForUserEvent{EventType::WaitForUser, data};
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
        for (std::size_t i = 0; i < events_.size(); ++i) {
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

} // namespace Movement::Movement
