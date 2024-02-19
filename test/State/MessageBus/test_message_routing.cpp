#include "Logging/Logger.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "State/MessageBus/Messages.hpp"

#include "DefaultUnitTest.hpp"
#include "State/MessageBus/Subscription.hpp"
#include "State/MessageBus/Broker.hpp"
#include "State/Machine/Machine.hpp"
#include "State/MessageBus/MachineRouter.hpp"
#include "Mocks/State/Machine/MockMachine.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace State::MessageBus;
using namespace State::Machine;
using namespace Mocks::State::Machine;

class MachineSubscriptionIntegrationTest : public DefaultUnitTest {
    
};

TEST_F(MachineSubscriptionIntegrationTest, should_send_start_message_to_machine) {
//GTEST_SKIP();
    MockMachine fsm;
    Broker broker;

    EXPECT_CALL(fsm, ExecuteStartMock()).Times(1);

    MachineRouter machineRouter(fsm);

    Subscription machineSubscription = Subscription(machineRouter, machineRouter.GetValidMessagesList());

    broker.subscribe(machineSubscription);

    StartMessage startMessage;

    broker.receive(startMessage);

    machineRouter.ProcessQueue();

}

TEST(MessageRouter, MessageRouter_logs_unknown_message) {
    Mocks::Logging::MockLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH> mockBackend;
    ELSF_LOG_INIT(mockBackend);

    EXPECT_CALL(mockBackend, LogFormattedWarn(testing::_)).Times(1);
    
    MockMachine fsm;
    MachineRouter machineRouter(fsm);
    StartMessage startMessage;

    machineRouter.on_receive_unknown(startMessage);
    LogSingleton::destroy();
}