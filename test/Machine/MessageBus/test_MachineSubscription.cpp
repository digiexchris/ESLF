#include "Logging/Logger.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "Machine/MessageBus/Messages.hpp"

#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/LoggingUnitTest.hpp"
#include "Machine/MessageBus/Subscription.hpp"
#include "Machine/MessageBus/Broker.hpp"
#include "Machine/FSM/Machine.hpp"
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Mocks/Machine/FSM/MockMachine.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>


using namespace Machine::MessageBus;
using namespace Machine::FSM;
using namespace Mocks::Machine::FSM;

class MachineSubscriptionTest : public DefaultUnitTest {
    
};

TEST_CASE_METHOD(MachineSubscriptionTest, "should_send_start_message_to_machine", "[Machine][MessageBus][Router]") {
//GTEST_SKIP();
    MockMachine fsm;
    Broker broker;

    REQUIRE_CALL(fsm, ExecuteStart()).TIMES(1);

    MachineRouter machineRouter(fsm);

    Subscription machineSubscription = Subscription(machineRouter, machineRouter.GetValidMessagesList());

    broker.subscribe(machineSubscription);

    StartMessage startMessage;

    broker.receive(startMessage);

    machineRouter.ProcessQueue();

}

TEST_CASE_METHOD(MachineSubscriptionTest, "constructor_starts_fsm", "[Machine][MessageBus][Router]") 
{
    MockMachine fsm;

    MachineRouter machineRouter(fsm);

    REQUIRE(fsm.is_started());
}

class MessageRouterLoggingTest : public LoggerTest
{
};

TEST_CASE_METHOD(MessageRouterLoggingTest, "MessageRouter_logs_unknown_message", "[Machine][MessageBus][Router]") 
{
    Mocks::Logging::MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockBackend;
    bool result = LogFactory<256>::Create(mockBackend);
    REQUIRE(result);
    REQUIRE_CALL(mockBackend, WarnMock(trompeloeil::_)).TIMES(1);
    REQUIRE_CALL(mockBackend, InfoMock(trompeloeil::_)).TIMES(1); //just because the FSM logs info when it starts
    MockMachine fsm;
    MachineRouter machineRouter(fsm);
    StartMessage startMessage;

    machineRouter.on_receive_unknown(startMessage);
    LogSingleton::destroy();
}