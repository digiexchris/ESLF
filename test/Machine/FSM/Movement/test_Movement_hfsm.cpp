#include <catch2/catch_all.hpp>
#include <typeinfo>

#include "Device/VirtualEncoder.hpp"
#include "Machine/FSM/Movement/Movement_event_data.hpp"
#include "Machine/FSM/Movement/Movement_generated_states.hpp"
#include "catch2/catch_test_macros.hpp"

using namespace Movement::Movement;

TEST_CASE("RootState", "[Machine][FSM][Movement]")
{
    SECTION("Init")
    {
        Movement::Movement::Root fsm;
        fsm.initialize();
        StateBase* child = fsm.getActiveChild();
        StateBase* leaf = fsm.getActiveLeaf();
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Stopped));
    }
}

TEST_CASE("TurningState, Auto Mode Off", "[Machine][FSM][Movement]")
{
    Movement::Movement::Root fsm;
    fsm.initialize();
    StateBase* child = fsm.getActiveChild();
    StateBase* leaf = fsm.getActiveLeaf();
    SECTION("Init") {
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Stopped));
    }

    SECTION("Configure")
    {
        //Send setDestination event
        //REQUIRE that the destination position is correct
        //Send set start position event
        //REQUIRE that the start position is correct
        //send set auto mode event = false
        //REQUIRE that the auto mode is false
        //send set direction
        //REQUIRE that the direction is correct
        //Check that it goes back into Stopped
    }
    
    SECTION("StartEvent")
    {
        
        StartRunningEventData data;
        fsm.spawn_StartRunning_event(data);
        
        fsm.handle_all_events();
        child = fsm.getActiveChild();
        leaf = fsm.getActiveLeaf();
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Running::WaitingForUser));
        
    }

    SECTION("Start Pass")
    {
        NextPassEventData data;
        fsm.spawn_NextPass_event(data);
        fsm.handle_all_events();
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Running::WaitForSync));
    }

    SECTION("In Sync")
    {
        fsm.tick(); //In the encoder tick, set the virtual encoder position == the motor position
        //Transition to moving
    }

    SECTION("Moving")
    {
        //tick a few times, each tick should update positions and execute motor moves
        //once at the destination, tick should transition to at destination
    }

    SECTION("At Destination")
    {
        //this tick should not do motor moves
        //Transition to wait for user
    }

    SECTION("Test that the user's return to start works")
    {

    }

    SECTION("Test that the user's manual moves work")
    {

    }

    SECTION("Test that starting the next pass from an arbitrary position works")
    {

    }
}