#include "Logging/Logger.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "State/MessageBus/Messages.hpp"

#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/LoggingUnitTest.hpp"
#include "State/MessageBus/Subscription.hpp"
#include "State/MessageBus/Broker.hpp"
#include "State/Machine/Machine.hpp"
#include "State/MessageBus/MachineRouter.hpp"
#include "Mocks/State/Machine/MockMachine.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace State::MessageBus;

class MessagesTest : public DefaultUnitTest {
    
};

TEST_F(MessagesTest, messages_with_params_store_corectly) {
    StartAtMessage startAtMessage(100);
    StopAtMessage stopAtMessage(200);

    ASSERT_EQ(startAtMessage.position, 100);
    ASSERT_EQ(stopAtMessage.position, 200);
}