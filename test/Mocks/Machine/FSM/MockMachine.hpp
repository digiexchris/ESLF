
#include <trompeloeil.hpp>
#include "Machine/FSM/Machine.hpp"
#include "Logging/Logger.hpp"

namespace Mocks::Machine::FSM {

class MockMachine : public ::Machine::FSM::MachineFSM
{
public:

  MAKE_MOCK0(ExecuteStart, void());
  MAKE_MOCK1(ExecuteStartAt, void(int));
  MAKE_MOCK0(ExecuteStop, void());
  MAKE_MOCK1(ExecuteStopAt,void(int));
  MAKE_MOCK0(ExecuteEStop, void());
  MAKE_MOCK0(ExecuteReset,void());
  
  // virtual void ExecuteStart() override {
  //   ExecuteStartMock();
  // }
};

} // namespace State::Machine