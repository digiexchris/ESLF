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
#include "Mocks/Machine/MessageBus/MockMachineRouter.hpp"
#include "trompeloeil/mock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>


using namespace Machine::MessageBus;
using namespace Machine::FSM;
using namespace Mocks::Machine::FSM;
using namespace Machine::MessageBus;

class MachineSubscriptionTest : public DefaultUnitTest {
    
};

TEST_CASE_METHOD(MachineSubscriptionTest, "should_send_start_message_to_machine", "[Machine][MessageBus][Router]") {
//GTEST_SKIP();
    MockMachine fsm;
    Broker broker;

    REQUIRE_CALL(fsm, ExecuteStart()).TIMES(1);

    MachineRouter machineRouter(fsm);
    machineRouter.Start();

    REQUIRE(fsm.is_started());

    Subscription machineSubscription = Subscription(machineRouter, machineRouter.GetValidMessagesList());

    broker.subscribe(machineSubscription);

    StartMessage startMessage;

    broker.receive(startMessage);

    machineRouter.ProcessQueue();

}

class MessageRouterLoggingTest : public LoggerBaseTest
{
};

TEST_CASE_METHOD(MessageRouterLoggingTest, "MessageRouter_logs_unknown_message", "[Machine][MessageBus][Router]") 
{
    Mocks::Logging::MockLogBackend* mockBackend = new Mocks::Logging::MockLogBackend();
    LogSingleton::create(std::move(mockBackend));
    REQUIRE(LogSingleton::is_valid());
    REQUIRE_CALL(*mockBackend, Warn(trompeloeil::_)).TIMES(1);
    REQUIRE_CALL(*mockBackend, Info(trompeloeil::_)).TIMES(1); //the default Startup log
    MockMachine fsm;
    MachineRouter machineRouter(fsm);
    machineRouter.Start();
    StartMessage startMessage;

    machineRouter.on_receive_unknown(startMessage);
    LogSingleton::destroy();
}

TEST_CASE_METHOD(MessageRouterLoggingTest, "QueuedRouter Recieve and ProcessQueue", "[Machine][MessageBus][Router]") 
{
    
    Mocks::Logging::MockLogBackend* mockBackend = new Mocks::Logging::MockLogBackend();
    LogSingleton::create(mockBackend);
    REQUIRE(LogSingleton::is_valid());
    REQUIRE_CALL(*mockBackend, Info(trompeloeil::_)).TIMES(2); //once for starting the queue, once for emplacing the message
    REQUIRE_CALL(*mockBackend, Error(trompeloeil::_)).TIMES(1); //for the unknown message
    MockMachine fsm;
    Mocks::Machine::MessageBus::TestQueuedRouter machineRouter;
    StartMessage startMessage;
    EStopMessage eStopMessage;
    REQUIRE_CALL(machineRouter, on_receive(trompeloeil::_)).TIMES(1);

    //shouldn't make it to on_receive_unknown, since the queue only accepts certain messages
    REQUIRE_CALL(machineRouter, on_receive_unknown(trompeloeil::_)).TIMES(0);

    machineRouter.receive(startMessage);
    machineRouter.receive(eStopMessage);
    machineRouter.ProcessQueue();
    machineRouter.ProcessQueue();

    LogSingleton::destroy();
}