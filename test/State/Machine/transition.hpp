#pragma once
#include <gtest/gtest.h>
#include <etl/vector.h>
#include "State/Machine/Machine.hpp"

struct TransitionCase {
public:
    TransitionCase(MachineMessageInterface& message_, MachineStateId toState_) :
        // fromState(fromState_),
        message(message_),
        toState(toState_) {
    }
    // ~TransitionCase() {
    //     if(message != nullptr) {
    //         delete message;
    //         message = nullptr;
    //     }
    // }
    // MachineStateId fromState;
    MachineMessageInterface& message;
    MachineStateId toState;
};

// template <size_t N>
// class TransitionTest : public testing::Test {
        
//  protected:
//   // Remember that SetUp() is run immediately before a test starts.
//   // This is a good place to record the start time.
// //   virtual void SetUp() override { start_time_ = time(nullptr); }

//   // TearDown() is invoked immediately after a test finishes.  Here we
//   // check if the test was too slow.
// //   void TearDown() override {
// //     transitions.clear();
// //   }

//     ~TransitionTest() override {
//         transitions.clear();
//     }

//     TransitionCase transitions[];
// };