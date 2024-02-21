#define GTEST_CATCH_EXCEPTIONS 0
#include <gtest/gtest.h>
#include "Machine/FSM/Machine.hpp"
#include "Machine/FSM/Running.hpp"
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

using namespace Machine::FSM;
using namespace Machine::MessageBus;

class TransitionFromInitTest : public DefaultUnitTest {
protected:
};

TEST_F(TransitionFromInitTest, one_transition_from_reset) {
    MachineFSM fsm;
    fsm.start();

    struct Transition {
        std::shared_ptr<etl::imessage> message;
        MachineStateId expectedState;
    };

    const Transition transitions[] = {
        { std::make_shared<StartMessage>(), MachineStateId::RUNNING },
        { std::make_shared<StartAtMessage>(100), MachineStateId::IDLE },
        { std::make_shared<StopMessage>(), MachineStateId::IDLE },
        { std::make_shared<StopAtMessage>(200), MachineStateId::IDLE },
        { std::make_shared<EStopMessage>(), MachineStateId::ESTOP },
        { std::make_shared<ResetMessage>(), MachineStateId::IDLE }
    };

    for (const auto& transition : transitions) {
        fsm.reset();
        fsm.start();

        etl::fsm_state_id_t currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(MachineStateId::IDLE)) << "State is not IDLE after reset for transition";

        std::shared_ptr<etl::imessage> message = transition.message;

        fsm.receive(*message);

        currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(transition.expectedState)) << "Transition failed";

    }
}
