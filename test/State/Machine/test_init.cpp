#define GTEST_CATCH_EXCEPTIONS 0
#include <gtest/gtest.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/Running.hpp"
#include "State/Machine/Idle.hpp"
#include "State/Machine/EStop.hpp"
#include "State/Machine/Messages.hpp"
#include <stdint.h>
#include <etl/vector.h>
#include <etl/utility.h>
#include <etl/iterator.h>
#include <etl/memory.h> // Include for etl::shared_ptr
#include <etl/message_packet.h>
#include <memory>
//#include "Logging/TestLogBackend.hpp"
#include "Logging/Logger.hpp"
#include "DefaultUnitTest.hpp"

class TransitionFromInitTest : public DefaultUnitTest {
protected:
    void SetUp() override {
        //GTEST_SKIP() << "Skipping all tests for this fixture";
        //ESLF_LOG_INIT(new TestLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH, 8>());
        //GTEST_FLAG_SET(catch_exceptions, false);
    }
    // void SetUp() override {
    //     //transitions.clear();
    //     //TODO I wonder if it's trying to access uninitialized transitions 
    //     transitions= etl::vector<TransitionCase,6>( {
    //         TransitionCase( MachineStateId::IDLE, new StartMessage(), MachineStateId::RUNNING ),
    //         TransitionCase( MachineStateId::IDLE, new StartAtMessage(0.0), MachineStateId::IDLE ),
    //         TransitionCase( MachineStateId::IDLE, new StopMessage(), MachineStateId::IDLE ),
    //         TransitionCase( MachineStateId::IDLE, new StopAtMessage(0.0), MachineStateId::IDLE ),
    //         TransitionCase( MachineStateId::IDLE, new EStopMessage(), MachineStateId::ESTOP ),
    //         TransitionCase( MachineStateId::IDLE, new ResetMessage(), MachineStateId::IDLE )

    //     });
    // };
};

TEST_F(TransitionFromInitTest, one_transition_from_reset) {
    Machine fsm;
    RunningState runningState;
    IdleState idleState;
    EStopState eStopState;

    // The list of states.
    etl::ifsm_state* stateList[] = { &idleState, &runningState, &eStopState };

    fsm.set_states(stateList, 3);
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
        //etl::send_message(fsm,*message);
        // #CCHATELAIN todo: remove this from the fsm, have the fsm as a reciever. Going to use a message bus for multiple routers/recievers. fsm.process_queue();

        currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(transition.expectedState)) << "Transition failed";

        //delete transition.message;  // Clean up the message
    }
}
