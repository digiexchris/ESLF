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
GTEST_SKIP();
    MockMachine *fsm = new MockMachine();
    Broker broker;

    MachineRouter machineRouter(fsm);

    Subscription machineSubscription = Subscription(machineRouter, machineRouter.GetValidMessagesList());

    broker.subscribe(machineSubscription);

    StartMessage startMessage;

    broker.receive(startMessage);

    machineRouter.ProcessQueue();

    EXPECT_CALL(*fsm, ExecuteStart()).Times(1);

    EXPECT_EQ(fsm->get_state_id(), MachineStateId::RUNNING);

    // if(fsm != nullptr) {
    //     delete fsm;
    // }
}

// TEST_F(MessageRoutingTest, should_send_start_at_message_to_machine_and_not_ui) {
//     Broker broker;

//     StartAtMessage startAtMessage(100);
// }