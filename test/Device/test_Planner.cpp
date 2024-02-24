#include <catch2/catch_test_macros.hpp>

#include "Device/VirtualEncoder.hpp"
#include "Device/VirtualMotor.hpp"
#include "Machine/Planner/ZOnly.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"

class PlannerTest : public DefaultUnitTest 
{
public:
    Machine::Planner::ZOnly<Device::VirtualEncoder, Device::VirtualEncoder,Device::VirtualMotor> planner;
};