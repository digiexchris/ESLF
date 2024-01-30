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

class TransitionFromInitTest : public testing::Test {
protected:
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
        etl::imessage* message;
        MachineStateId expectedState;
    };

    const Transition transitions[] = {
        { new StartMessage(), MachineStateId::RUNNING },
        { new StartAtMessage(100), MachineStateId::IDLE },
        { new StopMessage(), MachineStateId::IDLE },
        { new StopAtMessage(200), MachineStateId::IDLE },
        { new EStopMessage(), MachineStateId::ESTOP },
        { new ResetMessage(), MachineStateId::IDLE }
    };

    for (const auto& transition : transitions) {
        fsm.reset();
        fsm.start();

        etl::fsm_state_id_t currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(MachineStateId::IDLE)) << "State is not IDLE after reset for transition";

        etl::send_message(fsm, *transition.message);
        fsm.process_queue();

        currentState = fsm.get_state_id();
        ASSERT_EQ(currentState, static_cast<int>(transition.expectedState)) << "Transition failed";

        delete transition.message;  // Clean up the message
    }
}
