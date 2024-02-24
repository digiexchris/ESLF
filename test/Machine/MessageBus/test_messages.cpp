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

using namespace Machine::MessageBus;

class MessagesTest : public DefaultUnitTest {
    
};

TEST_CASE_METHOD(MessagesTest, "messages_with_params_store_corectly", "[MessageBus]") {
    StartAtMessage startAtMessage(100);
    StopAtMessage stopAtMessage(200);

    REQUIRE(startAtMessage.position == 100);
    REQUIRE(stopAtMessage.position == 200);
}