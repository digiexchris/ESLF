// #include "Machine/FSM/test_fsm.hpp"
// #include "catch2/catch_test_macros.hpp"

// #include "Machine/FSM/Base.hpp"
// #include "Machine/FSM/EStop.hpp"
// #include "Machine/FSM/Idle.hpp"
// #include "Machine/FSM/Turning.hpp"
// #include "Machine/MessageBus/Messages.hpp"
// #include "TestHelpers/DefaultUnitTest.hpp"
// #include "test_fsm.hpp"
// #include <etl/iterator.h>
// #include <etl/memory.h> // Include for etl::shared_ptr
// #include <etl/message_packet.h>
// #include <etl/utility.h>
// #include <etl/vector.h>
// #include <memory>

// using namespace Machine::FSM;
// using namespace Machine::MessageBus;

// class TransitionFromInitTest : public DefaultUnitTest
// {
// protected:
// };

// TEST_CASE_METHOD(TransitionFromInitTest, "one_transition_from_reset", "[Machine][FSM][Init]")
// {
//     TestFSM fsm;
//     fsm.Start();

//     struct Transition
//     {
//         std::shared_ptr<etl::imessage> message;
//         MachineStateId expectedState;
//     };

//     const Transition transitions[] = {{std::make_shared<StartMessage>(), MachineStateId::IDLE},
//                                       {std::make_shared<StopMessage>(), MachineStateId::IDLE},
//                                       {std::make_shared<EStopMessage>(), MachineStateId::ESTOP},
//                                       {std::make_shared<SetTurningMode>(), MachineStateId::STOPPED},
//                                       {std::make_shared<ResetMessage>(), MachineStateId::IDLE}};

//     for (const auto& transition : transitions)
//     {
//         fsm.reset();
//         fsm.start();

//         etl::fsm_state_id_t currentState = fsm.get_state_id();
//         REQUIRE(currentState ==
//                 static_cast<int>(
//                     MachineStateId::IDLE)); // << "State is not IDLE after reset for transition";

//         std::shared_ptr<etl::imessage> message = transition.message;

//         fsm.receive(*message);

//         currentState = fsm.get_state_id();
//         REQUIRE(currentState ==
//                 static_cast<int>(transition.expectedState)); // << "Transition failed";
//     }
// }
