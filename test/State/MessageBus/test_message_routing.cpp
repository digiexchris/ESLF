#include "State/MessageBus/Messages.hpp"

#include "DefaultUnitTest.hpp"
#include "State/MessageBus/Subscription.hpp"
#include "State/MessageBus/Broker.hpp"
#include "State/Machine/Machine.hpp"
#include "State/MessageBus/MachineRouter.hpp"

using namespace State::MessageBus;
using namespace State::Machine;

class MessageRoutingTest : public DefaultUnitTest {
    
};

TEST_F(MessageRoutingTest, should_send_start_message_to_machine_and_ui) {

    Machine* fsm = new Machine();
    Broker broker;

    MachineRouter machineRouter(fsm);

    Subscription* machineSubscription = machineRouter.GetSubscription();

    broker.subscribe(*machineSubscription);

    StartMessage startMessage;
    //broker.send(startMessage);

}

TEST_F(MessageRoutingTest, should_send_start_at_message_to_machine_and_not_ui) {
    Broker broker;

    StartAtMessage startAtMessage(100);
}