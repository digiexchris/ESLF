#include <etl/message.h>
#include <catch2/catch_test_macros.hpp>

#include "Machine/FSM/Machine.hpp"
#include "Machine/FSM/Turning.hpp"
#include "Machine/FSM/Idle.hpp"
#include "Machine/FSM/EStop.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include <etl/vector.h>
#include <etl/utility.h>
#include <etl/iterator.h>
#include <etl/memory.h> // Include for etl::shared_ptr
#include <etl/message_packet.h>
#include <memory>
#include "TestHelpers/DefaultUnitTest.hpp"
#include <etl/hfsm.h>

using namespace Machine::FSM;
using namespace Machine::MessageBus;

class TransitionFromTurningTest : public DefaultUnitTest {
protected:

};

namespace test_turning {
    void Reset(MachineFSM& fsm, etl::imessage* message) {
        fsm.reset();
        fsm.start();
        fsm.receive(*message);
    }
}

TEST_CASE_METHOD(TransitionFromTurningTest, "one_transition_from_idle", "[Machine][FSM][Turning]") {
    MachineFSM fsm;
    auto initialStateMessage= StartMessage();
    test_turning::Reset(fsm, &initialStateMessage);

    struct Transition {
        std::shared_ptr<etl::imessage> message;
        MachineStateId expectedState;
    };

    const Transition transitions[] = {
        { std::make_shared<StartMessage>(), MachineStateId::TURNING },
        { std::make_shared<StartAtMessage>(100), MachineStateId::TURNING },
        { std::make_shared<StopMessage>(), MachineStateId::IDLE },
        { std::make_shared<StopAtMessage>(200), MachineStateId::TURNING },
        { std::make_shared<EStopMessage>(), MachineStateId::ESTOP },
        { std::make_shared<ResetMessage>(), MachineStateId::IDLE }
    };

    for (const auto& transition : transitions) {
        test_turning::Reset(fsm, &initialStateMessage);

        etl::fsm_state_id_t currentState = fsm.get_state_id();
        REQUIRE(currentState == static_cast<int>(MachineStateId::TURNING));// << "State is not RUNNING after reset for transition";

        std::shared_ptr<etl::imessage> message = transition.message;

        fsm.receive(*message);
        currentState = fsm.get_state_id();
        REQUIRE(currentState == static_cast<int>(transition.expectedState));// << "Transition failed";
    }
}