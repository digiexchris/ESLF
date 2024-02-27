#include <catch2/catch_test_macros.hpp>

#include "Device/VirtualEncoder.hpp"
#include "Device/VirtualMotor.hpp"
#include "Logging/Logger.hpp"
#include "Machine/Planner/ZOnly.hpp"
#include "Device/Axis.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"

using namespace Machine::Planner;


class PlannerTest : public ZOnly<Device::VirtualEncoder, Device::VirtualMotor> 
{
public:

    Device::VirtualEncoder mainSpindle;
    Device::VirtualMotor zAxisMotor;
    Device::Axis<Device::VirtualMotor> zAxis;
    PlannerTest() : zAxisMotor(), zAxis('z', zAxisMotor), mainSpindle(), ZOnly(mainSpindle, zAxis)
    {

    }

    ~PlannerTest()
    {

    }
};

TEST_CASE_METHOD(PlannerTest, "Planner: ZOnly: Constructor", "[Planner]")
{

    start();
    Update();
    //REQUIRE(planner.GetState() == Machine::Planner::State::Idle);
}