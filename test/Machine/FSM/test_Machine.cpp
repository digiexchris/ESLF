// #include "Logging/Logger.hpp"
// #include "Machine/FSM/Base.hpp"
// #include "Mocks/Logging/MockLogBackend.hpp"
// #include "trompeloeil/mock.hpp"
// #include <catch2/catch_all.hpp>

// #include <Mocks/Machine/FSM/MockFSM.hpp>
// #include <TestHelpers/DefaultUnitTest.hpp>

// // using Mocks::Machine::FSM::MockBaseMachine;
// using trompeloeil::_;
// class BaseFSMTest : public Machine::FSM::BaseFSM, DefaultUnitTest
// {
// public:
//     MAKE_MOCK2(set_states, void(etl::ifsm_state**, size_t));
// };

// // TEST_CASE_METHOD(BaseFSMTest, "Constructor Exceptions", "[Machine][FSM][BaseFSM]") {
// //   // SECTION("Constructor Exceptions") {

// //     // Mock the behavior of the getState() function
// //     REQUIRE_CALL(*this, set_states(_,_))
// //       .THROW(etl::fsm_exception("dfgv","",0));

// //     REQUIRE_THROWS_AS((){

// //     }, etl::fsm_exception);

// //   // }
// // }