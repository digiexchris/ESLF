
#include <gmock/gmock.h>
#include "State/Machine/Machine.hpp"
#include "Logging/Logger.hpp"

namespace Mocks::State::Machine {

class MockMachine : public ::State::Machine::Machine
{
public:
// virtual void ExecuteStart() override {
//     ELSF_LOG_INFO("MockMachine received ExecuteStart");
// }
  MOCK_METHOD(void, ExecuteStart, (), (override));
  MOCK_METHOD(void, ExecuteStartAt, (), (override));
  MOCK_METHOD(void, ExecuteStop, (), (override));
  MOCK_METHOD(void, ExecuteStopAt, (), (override));
  MOCK_METHOD(void, ExecuteEStop, (), (override));
  MOCK_METHOD(void, ExecuteReset, (), (override));
};

} // namespace State::Machine