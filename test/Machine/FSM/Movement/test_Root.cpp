#include "../src/Machine/FSM/Movement/Root.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("MovementTest - Set Turning Mode", "[Machine][FSM][Root]")
{
    // Arrange
    Movement movement;
    sml::sm<Movement> sm{movement};

    // Act
    sm.process_event(Movement::SetTurningModeEvent{});

    // Assert
    REQUIRE(sm.is(sml::state<Turning>));
}

TEST_CASE("MovementTest - SetSlottingModeEvent", "[Machine][FSM][Root]")
{
    // Arrange
    Movement movement;
    sml::sm<Movement> sm{movement};

    // Act
    sm.process_event(Movement::SetSlottingModeEvent{});

    // Assert
    REQUIRE(sm.is(sml::state<Slotting>));
}

TEST_CASE("MovementTest - ExitEventFromTurning", "[Machine][FSM][Root]")
{
    // Arrange
    Movement movement;
    sml::sm<Movement> sm{movement};
    sm.process_event(Movement::SetTurningModeEvent{});

    // Act
    sm.process_event(ExitEvent{});

    // Assert
    REQUIRE(sm.is(sml::state<Idle>));
}

TEST_CASE("MovementTest - ExitEventFromSlotting", "[Machine][FSM][Root]")
{
    // Arrange
    Movement movement;
    sml::sm<Movement> sm{movement};
    sm.process_event(Movement::SetSlottingModeEvent{});

    // Act
    sm.process_event(ExitEvent{});

    // Assert
    REQUIRE(sm.is(sml::state<Idle>));
}

TEST_CASE("MovementTest - ResetEventFromEStop", "[Machine][FSM][Root]")
{
    // Arrange
    Movement movement;
    sml::sm<Movement> sm{movement};
    sm.process_event(EStop::ResetEvent{});

    // Assert
    REQUIRE(sm.is(sml::state<Idle>));
}