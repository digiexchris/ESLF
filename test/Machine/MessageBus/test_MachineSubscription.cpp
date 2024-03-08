#include "Logging/Logger.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"

#include "Machine/FSM/Base.hpp"
#include "Machine/MessageBus/Broker.hpp"
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Machine/MessageBus/Subscription.hpp"
#include "Mocks/Machine/FSM/MockFSM.hpp"
#include "Mocks/Machine/MessageBus/MockMachineRouter.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/LoggingUnitTest.hpp"
#include "trompeloeil/mock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>
#include <etl/memory.h>

using namespace Machine::MessageBus;
using namespace Machine::FSM;
using namespace Mocks::Machine::FSM;
using namespace Machine::MessageBus;

class MachineSubscriptionTest : public DefaultUnitTest
{
};

TEST_CASE_METHOD(MachineSubscriptionTest, "Should send Turn Mode Message",
                 "[Machine][MessageBus][Router]")
{
    etl::unique_ptr<MockFSM> fsm(new MockFSM());
    
    MachineRouter machineRouter(fsm.get());
    REQUIRE(fsm->is_started());
    Broker broker;

    // TODO this expecation doesn't get called, I can't find the link between the broker, sending to
    // the router, and then the FSM running the state change or on_recieve for that message.
    REQUIRE_CALL(*fsm, ExecuteSetTurnMode()).TIMES(1);

    Subscription machineSubscription = Subscription(machineRouter, machineRouter.GetValidMessagesList());

    broker.subscribe(machineSubscription);

    SetTurningMode setTurnModeMessage;

    broker.receive(setTurnModeMessage);

    machineRouter.ProcessQueue();
}

class MessageRouterLoggingTest : public LoggerBaseTest
{
};

TEST_CASE_METHOD(MessageRouterLoggingTest, "MessageRouter_logs_unknown_message",
                 "[Machine][MessageBus][Router]")
{
    LogSingleton::create(std::move(new Mocks::Logging::MockLogBackend()));
    REQUIRE(LogSingleton::is_valid());
    Mocks::Logging::MockLogBackend* mockBackend = dynamic_cast<Mocks::Logging::MockLogBackend*>(LogSingleton::instance().GetBackend());
    REQUIRE_CALL(*mockBackend, Warn(trompeloeil::_)).TIMES(1);
    REQUIRE_CALL(*mockBackend, Info(trompeloeil::_)).TIMES(1);
    etl::unique_ptr<MockFSM> fsm(new MockFSM());
    MachineRouter machineRouter(fsm.get());
    StartMessage startMessage;

    machineRouter.on_receive_unknown(startMessage);
    LogSingleton::destroy();
}

TEST_CASE_METHOD(MessageRouterLoggingTest, "QueuedRouter Recieve and ProcessQueue",
                 "[Machine][MessageBus][Router]")
{

    auto* mockBackend = new Mocks::Logging::MockLogBackend();
    LogSingleton::create(mockBackend);
    REQUIRE(LogSingleton::is_valid());
    REQUIRE_CALL(*mockBackend, Info(trompeloeil::_))
        .TIMES(3); // once for starting the queue, once for emplacing the message
    REQUIRE_CALL(*mockBackend, Error(trompeloeil::_)).TIMES(1); // for the unknown message
    MockFSM fsm;
    Mocks::Machine::MessageBus::TestQueuedRouter machineRouter;
    StartMessage startMessage;
    EStopMessage eStopMessage;
    REQUIRE_CALL(machineRouter, on_receive(trompeloeil::_)).TIMES(1);

    // shouldn't make it to on_receive_unknown, since the queue only accepts certain messages
    REQUIRE_CALL(machineRouter, on_receive_unknown(trompeloeil::_)).TIMES(0);

    machineRouter.receive(startMessage);
    machineRouter.receive(eStopMessage);
    machineRouter.ProcessQueue();
    machineRouter.ProcessQueue();

    LogSingleton::destroy();
}