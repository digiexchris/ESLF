#include "Machine/FSM/Movement/Root.hpp"
#include "Machine/FSM/Movement/SM.hpp"
#include "Machine/FSM/Movement/Turning.hpp"
#include "Machine/FSM/sml.hpp"
#include <catch2/catch_all.hpp>

using namespace boost;

// sml::sm<example, sml::thread_safe<std::recursive_mutex>> sm; // thread safe policy
// sml::sm<example, sml::logger<my_logger>> sm; // logger policy
// sml::sm<example, sml::thread_safe<std::recursive_mutex>, sml::logger<my_logger>> sm; // thread
// safe and logger policy sml::sm<example, sml::logger<my_logger>,
// sml::thread_safe<std::recursive_mutex>> sm; // thread safe and logger policy

TEST_CASE("MovementTest - Set Turning Mode", "[Machine][FSM][Root]")
{
    // Arrange
    // MovementSM m;
    sm<Turning<>> sm{}; // thread safe policy

    // Act
    // sm.process_event(Movement::SetTurningModeEvent{});

    // Assert
    // REQUIRE(sm.is(sml::state<Turning<>::WaitForUser::Waiting>));
}

// TEST_CASE("MovementTest - SetSlottingModeEvent", "[Machine][FSM][Root]")
// {
//     sml::sm<MovementSM> sm;

//     // Act
//     sm.process_event(Movement::SetSlottingModeEvent());

//     // Assert
//     REQUIRE(sm.is(sml::state<Slotting>));
// }

// TEST_CASE("MovementTest - ExitEventFromTurning", "[Machine][FSM][Root]")
// {
//     // Arrange
//     sml::sm<MovementSM> sm;
//     sm.process_event(Movement::SetTurningModeEvent{});

//     // Act
//     sm.process_event(ExitEvent{});

//     // Assert
//     REQUIRE(sm.is(sml::state<Idle>));
// }

// TEST_CASE("MovementTest - ExitEventFromSlotting", "[Machine][FSM][Root]")
// {
//     // Arrange
//     sml::sm<MovementSM> sm;
//     sm.process_event(Movement::SetSlottingModeEvent{});

//     // Act
//     sm.process_event(ExitEvent{});

//     // Assert
//     REQUIRE(sm.is(sml::state<Idle>));
// }

// TEST_CASE("MovementTest - ResetEventFromEStop", "[Machine][FSM][Root]")
// {
//     // Arrange
//     sml::sm<MovementSM> sm;
//     sm.process_event(EStop::ResetEvent{});

//     // Assert
//     REQUIRE(sm.is(sml::state<Idle>));
// }