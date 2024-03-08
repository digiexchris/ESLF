#include <catch2/catch_test_macros.hpp>
#include <etl/message.h>

#include "Machine/FSM/Base.hpp"
#include "Machine/FSM/EStop.hpp"
#include "Machine/FSM/Idle.hpp"
#include "Machine/FSM/Turning.hpp"
#include "Machine/FSM/test_fsm.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"
#include <etl/hfsm.h>
#include <etl/iterator.h>
#include <etl/memory.h> // Include for etl::shared_ptr
#include <etl/message_packet.h>
#include <etl/utility.h>
#include <etl/vector.h>
#include <memory>

using namespace Machine::FSM;
using namespace Machine::MessageBus;

class TransitionFromTurningTest : public DefaultUnitTest
{
protected:
};

TEST_CASE_METHOD(TransitionFromTurningTest, "moving_from_turning", "[Machine][FSM][Turning]")
{
    TestFSM fsm;
    fsm.start();
    REQUIRE(fsm.get_state_id() == MachineStateId::IDLE);

    StartMessage startMessage;
    fsm.receive(startMessage);

    REQUIRE(fsm.get_state_id() == MachineStateId::IDLE); // it should not change to Moving from Idle

    // REQUIRE(fsm.get_state_id() == MachineStateId::TURNING);
    auto turnModeMessage = SetTurningMode();
    fsm.receive(turnModeMessage);

    REQUIRE(fsm.get_state_id() == MachineStateId::STOPPED);

    auto start2 = StartMessage();
    fsm.receive(start2);
    REQUIRE(fsm.get_state_id() == MachineStateId::MOVING);

    // TODO add requirement to not be able to switch from turn to thread while moving

    auto stopMessage = StopMessage();

    fsm.receive(stopMessage);

    REQUIRE(fsm.get_state_id() == MachineStateId::STOPPED);

    fsm.receive(startMessage);
    REQUIRE(fsm.get_state_id() == MachineStateId::MOVING);

    auto resetMessage = ResetMessage();

    fsm.receive(resetMessage);

    REQUIRE(fsm.get_state_id() == MachineStateId::IDLE);
}

// TEST_CASE_METHOD(TransitionFromTurningTest, "moving to stopped", "[Machine][FSM][Turning]") {
//     BaseFSM fsm;
//     auto initialStateMessage= SetTurningMode();
//     test_turning::Reset(fsm, &initialStateMessage);

//     REQUIRE(fsm.get_state_id() == MachineStateId::TURNING);

//     StartMessage startMessage;
//     StopMessage stopMessage;

//     fsm.receive(startMessage);

//     REQUIRE(fsm.get_state_id() == MachineStateId::MOVING);

//     fsm.receive(stopMessage);

//     REQUIRE(fsm.get_state_id() == MachineStateId::STOPPED);
// }

// TEST_CASE_METHOD(TransitionFromTurningTest, "moving to reset", "[Machine][FSM][Turning]") {
//     BaseFSM fsm;
//     auto initialStateMessage= SetTurningMode();
//     test_turning::Reset(fsm, &initialStateMessage);

//     REQUIRE(fsm.get_state_id() == MachineStateId::TURNING);

//     StartMessage startMessage;
//     ResetMessage resetMessage;

//     fsm.receive(startMessage);

//     REQUIRE(fsm.get_state_id() == MachineStateId::MOVING);

//     fsm.receive(resetMessage); //this SHOULD halt any further moves because the update() checks
//     state before moving.

//     REQUIRE(fsm.get_state_id() == MachineStateId::IDLE);
// }