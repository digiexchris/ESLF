#include <etl/message.h>
#define GTEST_CATCH_EXCEPTIONS 0
#include <gtest/gtest.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/Running.hpp"
#include "State/Machine/Idle.hpp"
#include "State/Machine/EStop.hpp"
#include "State/MessageBus/Messages.hpp"
#include <etl/vector.h>
#include <etl/utility.h>
#include <etl/iterator.h>
#include <etl/memory.h> // Include for etl::shared_ptr
#include <etl/message_packet.h>
#include <memory>
#include "TestHelpers/DefaultUnitTest.hpp"
#include <etl/hfsm.h>

using namespace State::Machine;
using namespace State::MessageBus;

class TransitionFromRunningTest : public DefaultUnitTest {
protected:

};

namespace test_running {
    void Reset(Machine& fsm, etl::imessage* message) {
        fsm.reset();
        fsm.start();
        fsm.receive(*message);
    }
}

TEST_F(TransitionFromRunningTest, one_transition_from_idle) {
    Machine fsm;
    auto initialStateMessage= StartMessage();
    test_running::Reset(fsm, &initialStateMessage);

    struct Transition {
        std::shared_ptr<etl::imessage> message;
        MachineStateId expectedState;
    };

    const Transition transitions[] = {
        { std::make_shared<StartMessage>(), MachineStateId::RUNNING },
        { std::make_shared<StartAtMessage>(100), MachineStateId::RUNNING },
        { std::make_shared<StopMessage>(), MachineStateId::IDLE },
        { std::make_shared<StopAtMessage>(200), MachineStateId::RUNNING },
        { std::make_shared<EStopMessage>(), MachineStateId::ESTOP },
        { std::make_shared<ResetMessage>(), MachineStateId::IDLE }
    };

    for (const auto& transition : transitions) {
        test_running::Reset(fsm, &initialStateMessage);

        etl::fsm_state_id_t currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(MachineStateId::RUNNING)) << "State is not RUNNING after reset for transition";

        std::shared_ptr<etl::imessage> message = transition.message;

        fsm.receive(*message);
        currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(transition.expectedState)) << "Transition failed";
    }
}
