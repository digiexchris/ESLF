#include <etl/message.h>
#define GTEST_CATCH_EXCEPTIONS 0
#include <gtest/gtest.h>
#include "Machine/FSM/Machine.hpp"
#include "Machine/FSM/EStop.hpp"
#include "Machine/FSM/Idle.hpp"
#include "Machine/FSM/Running.hpp"
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

class TransitionFromEStopTest : public DefaultUnitTest {
protected:

};

namespace test_EStop {
    void Reset(MachineFSM& fsm, etl::imessage* message) {
        fsm.reset();
        fsm.start();
        fsm.receive(*message);
    }
}

TEST_F(TransitionFromEStopTest, one_transition_from_idle) {
        MachineFSM fsm;
        RunningState runningState;
        IdleState idleState;
        EStopState eStopState;

        // The list of states.
        etl::ifsm_state* stateList[] = { &idleState,  &runningState, &eStopState };

        fsm.set_states(stateList, 3);

        auto initialStateMessage= EStopMessage();
       
       test_EStop::Reset(fsm, &initialStateMessage);

    struct Transition {
        std::shared_ptr<etl::imessage> message;
        MachineStateId expectedState;
    };

    const Transition transitions[] = {
        { std::make_shared<StartMessage>(), MachineStateId::ESTOP },
        { std::make_shared<StartAtMessage>(100), MachineStateId::ESTOP },
        { std::make_shared<StopMessage>(), MachineStateId::ESTOP },
        { std::make_shared<StopAtMessage>(200), MachineStateId::ESTOP },
        { std::make_shared<EStopMessage>(), MachineStateId::ESTOP },
        { std::make_shared<ResetMessage>(), MachineStateId::IDLE }
    };

    for (const auto& transition : transitions) {
        test_EStop::Reset(fsm, &initialStateMessage);

        etl::fsm_state_id_t currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(MachineStateId::ESTOP)) << "State is not EStop after reset for transition";

        std::shared_ptr<etl::imessage> message = transition.message;

        fsm.receive(*message);
        currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(transition.expectedState)) << "Transition failed";
    }
}
