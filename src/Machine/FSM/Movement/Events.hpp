#pragma once
#include "Movement_event_data.hpp"
#include "EventBase.hpp"

namespace Movement::Movement {
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
      virtual ~Event() = default;
      T get_data() const { return data; }
    }; // Class Event

    // free the memory associated with the event
    static void consume_event(GeneratedEventBase *e) {
      delete e;
    }

using AtDestinationEvent = Event<AtDestinationEventData>;
using AutoNextPassEvent = Event<AutoNextPassEventData>;
using AutoReturnToStartPositionEvent = Event<AutoReturnToStartPositionEventData>;
using EStopEvent = Event<EStopEventData>;
using MoveToEvent = Event<MoveToEventData>;
using NextPassEvent = Event<NextPassEventData>;
using ResetEvent = Event<ResetEventData>;
using ResumeLastStateEvent = Event<ResumeLastStateEventData>;
using ReturnToStartEvent = Event<ReturnToStartEventData>;
using SetAutoModeEvent = Event<SetAutoModeEventData>;
using StartRunningEvent = Event<StartRunningEventData>;
using StartMovingEvent = Event<StartMovingEventData>;
using StopEvent = Event<StopEventData>;
using WaitForUserEvent = Event<WaitForUserEventData>;

}; // namespace Movement::Movement