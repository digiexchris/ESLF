#pragma once
#include "EventTypes.hpp"
#include <string>
#include "magic_enum.hpp"

namespace Movement::Movement {

  // Base Class for Events, abstract so you never instantiate.
  class EventBase {
  public:
    virtual ~EventBase() = default;
    virtual std::string to_string() const = 0;
  }; // class EventBase

/**
     * @brief Class representing all events that this HFSM can respond
     * to / handle. Used as abstract interface for handleEvent().
     */
    class GeneratedEventBase : public EventBase {
    protected:
      EventType type;
    public:
      explicit GeneratedEventBase(const EventType& t) : type(t) {}
      virtual ~GeneratedEventBase() = default;
      EventType get_type() const { return type; }
      virtual std::string to_string() const {
        return std::string(magic_enum::enum_name(type));
      }
    }; // Class GeneratedEventBase

}; // namespace Movement::Movement