#include <catch2/catch_test_macros.hpp>

#include "Device/Axis.hpp"
#include "Device/VirtualEncoder.hpp"
#include "Device/VirtualMotor.hpp"
#include "Logging/Logger.hpp"
#include "Machine/FSM/Base.hpp"
#include "Machine/Manager/LatheZ.hpp"
#include "Machine/MessageBus/Broker.hpp"
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Machine/MessageBus/Messages.hpp"
#include "Machine/MessageBus/Subscription.hpp"
#include "Mocks/Logging/MockLogBackend.hpp"
#include "TestHelpers/DefaultUnitTest.hpp"
#include "TestHelpers/Logging/TestLogBackend.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Machine::Manager;

class ManagerTest : public DefaultUnitTest
{
public:
    template <typename MainSpindleEncoder, typename ZAxisMotor>
    class TestManager: public LatheZ<Device::VirtualEncoder, Device::VirtualMotor>
    {
        public:
        TestManager(MainSpindleEncoder& aMainSpindle, Device::Axis<ZAxisMotor>& anAxis) : LatheZ(aMainSpindle, anAxis)
        {
        }

        void EnableMotors() override
        {
        }
        void DisableMotors() override
        {
        }
    };

    ManagerTest()
    {
        mainSpindle.reset(new Device::VirtualEncoder());
        zAxisMotor.reset(new Device::VirtualMotor());
        zAxis.reset(new Device::Axis<Device::VirtualMotor>('z', *zAxisMotor));

        myManager.reset(new TestManager<Device::VirtualEncoder, Device::VirtualMotor>(*mainSpindle, *zAxis));

        broker.reset(new Machine::MessageBus::Broker());
        router.reset(new Machine::MessageBus::MachineRouter(myManager.get()));
        
        auto machineSubscription =
            Machine::MessageBus::Subscription(*router, router->GetValidMessagesList());
        broker->subscribe(machineSubscription);
    }

    etl::unique_ptr<TestManager<Device::VirtualEncoder, Device::VirtualMotor>> myManager;

    

    etl::unique_ptr<Machine::MessageBus::Broker> broker;
    etl::unique_ptr<Machine::MessageBus::MachineRouter> router;
    etl::unique_ptr<Device::VirtualEncoder> mainSpindle;
    etl::unique_ptr<Device::VirtualMotor> zAxisMotor;
    etl::unique_ptr<Device::Axis<Device::VirtualMotor>> zAxis;
};

SCENARIO_METHOD(ManagerTest, "TurningMode", "[Manager]")
{
    Machine::MessageBus::SetTurningMode turningMode;
    broker->receive(turningMode);
    router->ProcessQueue();

    REQUIRE(myManager->GetStateId() == Machine::FSM::MachineStateId::STOPPED);

    WHEN("The machine is stopped")
    {
        THEN("The motor should not move")
        {
            mainSpindle->SetCountIncrement(1);
            myManager->Update();
            REQUIRE(zAxis->GetPosition() == 0);
        }
    }

    WHEN("The machine is MOVING")
    {
        THEN("The motor should track the spindle position")
        {

            REQUIRE(zAxisMotor->IsEnabled() == false);
            Machine::MessageBus::StartMessage startMessage;
            broker->receive(startMessage);
            router->ProcessQueue();

            // TODO since the FSM needs to enable the axis on start, and disable it on estop, the
            // Manager probably needs to extend the FSM at least. Router doesn't need to be in
            // Manager or a parent of Manager in order to route to FSM it just needs a reference to
            // the FSM.

            REQUIRE(myManager->GetStateId() == Machine::FSM::MachineStateId::MOVING);
            REQUIRE(zAxisMotor->IsEnabled() == true);

            // NOTE: two different ways of doing a negative move: direction false with a positive
            // move, or direction true with a negative move
            mainSpindle->SetCountIncrement(1);
            mainSpindle->SetDirection(true);
            myManager->Update();
            REQUIRE(zAxis->GetPosition() == 1);
            mainSpindle->SetCountIncrement(10);
            myManager->Update();
            REQUIRE(zAxis->GetPosition() == 11);
            mainSpindle->SetCountIncrement(-100);
            myManager->Update();
            REQUIRE(zAxis->GetPosition() == -89);

            mainSpindle->SetDirection(false);
            mainSpindle->SetCountIncrement(100);
            myManager->Update();
            REQUIRE(zAxis->GetPosition() == -189);

            // TODO disable through the FSM, test that it didn't move. Making multiple protections
            // against movement with an e-stop, both the lack of generated moves, and disabling the
            // motor directly.
            zAxisMotor->Disable();
            //REQUIRE it should not move when updated. or should it enable? yeah maybe it should enable.
        }
    }
}