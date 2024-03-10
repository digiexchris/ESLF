#include <catch2/catch_all.hpp>
#include <typeinfo>

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

TEST_CASE("TurningState", "[Machine][FSM][Movement]")
{
    SECTION("StartEvent")
    {
        Movement::Movement::Root fsm;
        fsm.initialize();
        StartRunningEventData data;
        fsm.spawn_StartRunning_event(data);
        StateBase* child = fsm.getActiveChild();
        StateBase* leaf = fsm.getActiveLeaf();
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Stopped));
        fsm.handle_all_events();
        child = fsm.getActiveChild();
        leaf = fsm.getActiveLeaf();
        REQUIRE(typeid(*child) == typeid(Root::Turning));
        REQUIRE(typeid(*leaf)== typeid(Root::Turning::Running::WaitingForUser));
        
    }
}