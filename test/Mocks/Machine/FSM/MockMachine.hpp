
#include <gmock/gmock.h>
#include "Machine/FSM/Machine.hpp"
#include "Logging/Logger.hpp"

namespace Mocks::Machine::FSM {

class MockMachine : public ::Machine::FSM::MachineFSM
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