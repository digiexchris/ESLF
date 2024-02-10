#pragma once

/**
* @brief MockMachineRouter
* @details Mocks the MachineRouter class, 
* Allowing testing of the brokers and subscriptions
* Allows expectations against the on_receive methods
*/

#include <gmock/gmock.h>
#include "State/MessageBus/MachineRouter.hpp"
#include "State/MessageBus/Messages.hpp"

namespace Mocks::State::MessageBus {
using namespace ::State::MessageBus;
class MockMachineRouter : public ::State::MessageBus::MachineRouter
{
public:
    MOCK_METHOD(void, on_receive, (const StartMessage&), (override));
    MOCK_METHOD(void, on_receive, (const StartAtMessage&), (override));
    MOCK_METHOD(void, on_receive, (const StopMessage&), (override));
    MOCK_METHOD(void, on_receive, (const StopAtMessage&), (override));
    MOCK_METHOD(void, on_receive, (const EStopMessage&), (override));
    MOCK_METHOD(void, on_receive, (const ResetMessage&), (override));
    MOCK_METHOD(void, on_receive_unknown, (const etl::imessage&), (override));
};

} // namespace Mocks