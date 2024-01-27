#include <gtest/gtest.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/Running.hpp"
#include "State/Machine/Idle.hpp"
#include "State/Machine/Messages.hpp"
#include <stdint.h>
#include <etl/vector.h>
#include <etl/utility.h>
#include <etl/iterator.h>

// ZTEST_F(transition_to_turn, idle_to_start_no_delay) {

//     Machine fsm;

//     Running runningState;
//     InitState initState;

//     // The list of states.
//     etl::ifsm_state* stateList[] = { &initState, &runningState  };

//     // Set up the FSM
//     fsm.set_states(stateList, etl::size(stateList));
//     fsm.start();

//     // Queue all of the messages.
//     etl::send_message(fsm, StartMessage());

//     // De-queue them
//     fsm.process_queue();

//     etl::fsm_state_id_t currentState = fsm.get_state_id();

//     zassert_equal(currentState, MachineStateId::RUNNING, "State is not RUNNING");

//     etl::send_message(fsm, StopMessage());

//     // De-queue them
//     fsm.process_queue();

//     currentState = fsm.get_state_id();
//     zassert_equal(currentState, MachineStateId::IDLE, "State is not IDLE");

// }

TEST(transition_to_turn, idle_state_changes) {

    // auto * start = new StartMessage();
    // auto * startAt = new StartAtMessage(0);
    // auto * stop = new StopMessage();
    // auto * stopAt = new StopAtMessage(0);
    // auto * eStop = new EStopMessage();
    // auto * reset = new ResetMessage();

    //message, expected state
    etl::vector<etl::pair<etl::imessage*, MachineStateId>, 6> testCases = {
    etl::make_pair(new StartMessage(), MachineStateId::RUNNING),
    etl::make_pair(new StartAtMessage(0), MachineStateId::IDLE),
    etl::make_pair(new StopMessage(), MachineStateId::IDLE),
    etl::make_pair(new StopAtMessage(0), MachineStateId::IDLE),
    etl::make_pair(new EStopMessage(), MachineStateId::ESTOP),
    etl::make_pair(new ResetMessage(), MachineStateId::IDLE)
};

    Machine fsm;

    RunningState runningState;
    IdleState idleState;

    // The list of states.
    etl::ifsm_state* stateList[] = { &idleState, &runningState  };

    // Set up the FSM
    fsm.set_states(stateList, 2);

    for(etl::pair<etl::imessage*, MachineStateId> tc :testCases) {
        fsm.reset();
        fsm.start();

        etl::send_message(fsm, *tc.first);

        // De-queue them
        fsm.process_queue();

        etl::fsm_state_id_t currentState = fsm.get_state_id();

        EXPECT_EQ(currentState, static_cast<int>(tc.second));
    }
}