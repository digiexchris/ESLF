
#include <gmock/gmock.h>
#include "State/Machine/Machine.hpp"
#include "Logging/Logger.hpp"

namespace Mocks::State::Machine {

class MockMachine : public ::State::Machine::Machine
{
public:

  MOCK_METHOD(void, ExecuteStartMock, (), ());
  MOCK_METHOD(void, ExecuteStartAt, (), (override));
  MOCK_METHOD(void, ExecuteStop, (), (override));
  MOCK_METHOD(void, ExecuteStopAt, (), (override));
  MOCK_METHOD(void, ExecuteEStop, (), (override));
  MOCK_METHOD(void, ExecuteReset, (), (override));
  
  virtual void ExecuteStart() override {
    ExecuteStartMock();
  }
};

} // namespace State::Machine