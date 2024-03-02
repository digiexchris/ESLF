#include <catch2/catch_test_macros.hpp>

#include "Device/VirtualEncoder.hpp"
#include "Device/VirtualMotor.hpp"
#include "Logging/Logger.hpp"
#include "Machine/FSM/Machine.hpp"
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Machine/Planner/Planner1.hpp"
#include "Device/Axis.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/TestLogBackend.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Machine::Planner;


class PlannerTest : public Planner1<Device::VirtualEncoder, Device::VirtualMotor> 
{
public:
    Machine::FSM::MachineFSM* myFsm;
    Machine::MessageBus::MachineRouter router;
    Device::VirtualEncoder mainSpindle;
    Device::VirtualMotor zAxisMotor;
    Device::Axis<Device::VirtualMotor> zAxis;
    PlannerTest() : Planner1(mainSpindle, zAxis, router), zAxis('z', zAxisMotor)
    {
        ELSF_LOG_INIT(new TestLogBackend());
        myFsm = new Machine::FSM::MachineFSM();
        router.SetFsm(myFsm);
        router.Start();
        
    }

    ~PlannerTest()
    {
        LogSingleton::destroy();
    }

};

SCENARIO_METHOD(PlannerTest, "TurningMode", "[Planner]")
{
    Machine::MessageBus::SetTurningMode turningMode;
    myRouter.receive(turningMode);
    myRouter.ProcessQueue();

    REQUIRE(myRouter.GetFsm()->GetStateId() == Machine::FSM::MachineStateId::STOPPED);



    WHEN("The machine is stopped") {
        THEN("The motor should not move") {
            mainSpindle.SetCountIncrement(1);
            Update();
            REQUIRE(myZAxis.GetPosition() == 0);
        }
    }
    
    WHEN("The machine is MOVING") {
        THEN("The motor should track the spindle position") {    
            
            Machine::MessageBus::StartMessage startMessage;
            myRouter.receive(startMessage);
            myRouter.ProcessQueue();

            REQUIRE(myRouter.GetFsm()->GetStateId() == Machine::FSM::MachineStateId::MOVING);

            mainSpindle.SetCountIncrement(1);
            Update();
            REQUIRE(myZAxis.GetPosition() == 1);
            mainSpindle.SetCountIncrement(10);
            Update();
            REQUIRE(myZAxis.GetPosition() == 11);
            mainSpindle.SetCountIncrement(-100);
            Update();
            REQUIRE(myZAxis.GetPosition() == -89);
        }
    }
    
    
}