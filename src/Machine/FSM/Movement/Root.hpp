#include "../sml.hpp"
#include "CommonEvents.hpp"
#include <iostream>
namespace sml = boost::sml;
// Events

// forward declare states
struct Turning;
struct Movement;
struct Idle;
struct Slotting;
// States
struct Idle
{
    struct InitEvent
    {
    };
};

struct EStop // consider providing a callback that the implementer can use to restart the MCU if
             // required.
{
    struct ResetEvent
    {
    };
};

struct Movement
{

    struct SetTurningModeEvent
    {
    };

    struct SetSlottingModeEvent
    {
    };

    auto operator()() const noexcept
    {
        using namespace sml;
        // clang-format off
        return make_transition_table(
        * state<Idle> + event<Idle::InitEvent> = state<Idle>
        , state<Idle> + event<SetTurningModeEvent> / [] { std::cout << "enter sub sm" << std::endl; } = state<Turning>
        , state<Idle> + event<SetSlottingModeEvent> / [] { std::cout << "enter sub sm" << std::endl; } = state<Slotting>
        , state<Turning> + event<ExitEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<Idle>
        , state<Slotting> + event<ExitEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<Idle>
        , state<EStop> + event<EStop::ResetEvent> = state<Idle>
        );
        // clang-format on
    }
};

// EndStates
