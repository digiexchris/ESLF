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

TEST(idle_state, one_transition_from_reset) {
    // Define test cases using etl::shared_ptr
    etl::vector<etl::pair<etl::shared_ptr<etl::imessage>, MachineStateId>, 6> testCases = {
        etl::make_pair(etl::shared_ptr<etl::imessage>(new StartMessage()), MachineStateId::RUNNING),
        etl::make_pair(etl::shared_ptr<etl::imessage>(new StartAtMessage(0)), MachineStateId::IDLE),
        etl::make_pair(etl::shared_ptr<etl::imessage>(new StopMessage()), MachineStateId::IDLE),
        etl::make_pair(etl::shared_ptr<etl::imessage>(new StopAtMessage(0)), MachineStateId::IDLE),
        etl::make_pair(etl::shared_ptr<etl::imessage>(new EStopMessage()), MachineStateId::ESTOP),
        etl::make_pair(etl::shared_ptr<etl::imessage>(new ResetMessage()), MachineStateId::IDLE)
    };

    Machine fsm;
    RunningState runningState;
    IdleState idleState;
    EStopState eStopState;

    // The list of states.
    etl::ifsm_state* stateList[] = { &idleState, &runningState, &eStopState };

    // Set up the FSM
    fsm.set_states(stateList, 3);
    fsm.start();

    etl::fsm_state_id_t currentState = fsm.get_state_id();
    EXPECT_EQ(currentState, static_cast<int>(MachineStateId::IDLE)) << "State is not IDLE at start";

    for (auto& testCase : testCases) {
        size_t index = std::distance(testCases.begin(), &testCase);

        etl::send_message(fsm, ResetMessage());
        fsm.process_queue();

        currentState = fsm.get_state_id();
        EXPECT_EQ(currentState, static_cast<int>(MachineStateId::IDLE)) << "State is not IDLE after reset";

        etl::send_message(fsm, *testCase.first);

        fsm.process_queue();

        currentState = fsm.get_state_id();
        EXPECT_EQ(currentState, static_cast<int>(testCase.second)) << "Case " << index << " failed";
    }

    // No need for explicit cleanup; etl::shared_ptrs in the vector will automatically clean up
}
