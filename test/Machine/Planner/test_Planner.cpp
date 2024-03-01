#include <catch2/catch_test_macros.hpp>

#include "Device/VirtualEncoder.hpp"
#include "Device/VirtualMotor.hpp"
#include "Logging/Logger.hpp"
#include "Machine/FSM/Machine.hpp"
#include "Machine/Planner/Planner1.hpp"
#include "Device/Axis.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/TestLogBackend.hpp"
#include "Machine/MessageBus/Messages.hpp"

using namespace Machine::Planner;


class PlannerTest : public Planner1<Device::VirtualEncoder, Device::VirtualMotor> 
{
public:

    Device::VirtualEncoder mainSpindle;
    Device::VirtualMotor zAxisMotor;
    Device::Axis<Device::VirtualMotor> zAxis;
    PlannerTest() : zAxisMotor(), zAxis('z', zAxisMotor), mainSpindle(), Planner1(mainSpindle, zAxis)
    {
        myTestLogBackend = new TestLogBackend();
        ELSF_LOG_INIT(myTestLogBackend);

    }

    ~PlannerTest()
    {

    }

    private:
        TestLogBackend* myTestLogBackend;
};

TEST_CASE_METHOD(PlannerTest, "Planner: Planner1: Constructor", "[Planner]")
{

    //start();
    mainSpindle.SetCountIncrement(1);
    zAxis.
    Update();
    REQUIRE(myZAxis.GetPosition() == 1);
    //REQUIRE(get_state_id() == Machine::FSM::MachineStateId::IDLE);
    
}