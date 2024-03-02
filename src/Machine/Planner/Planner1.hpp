#pragma once
#include "Machine/FSM/Machine.hpp"
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Planner.hpp"
#include "State/Position.hpp"

namespace Machine::Planner
{
template <typename MainSpindleEncoder, typename ZAxisMotor>
class Planner1 : public Planner<MainSpindleEncoder>
{
    public:
        Planner1(
            MainSpindleEncoder& aMainSpindle, 
            Device::Axis<ZAxisMotor>& anAxis,
            MessageBus::MachineRouter& aMachineRouter);

        void Update() override;
        void GenerateMoves() override;

    protected:

        void GenerateThreadingMoves();
        void GenerateTurningMoves();

        Device::Axis<ZAxisMotor>& myZAxis;
};

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    Planner1<MainSpindleEncoder, ZAxisMotor>::Planner1(
            MainSpindleEncoder& aMainSpindle, 
            Device::Axis<ZAxisMotor>& anAxis, 
            MessageBus::MachineRouter& aMachineRouter
        ): Planner<MainSpindleEncoder>(aMainSpindle, aMachineRouter),
            myZAxis(anAxis)
        {
        }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::Update()
    {
        // Update the main spindle encoder
        this->myMainSpindleEncoder.Update();
        myZAxis.Update();
        GenerateMoves();
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateTurningMoves()
    {
        int32_t positionDifference = myZAxis.Diff(this->myMainSpindleEncoder);
        if (positionDifference != 0) 
        {

            //NOTE: both positions should be ints at this point, scaled internally
            //this currently is a 1:1 ratio, no gearing.
            myZAxis.MoveTo(myZAxis.GetPosition()-positionDifference);
        }

    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateThreadingMoves()
    {
        //To be implemented with the threading parent state
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateMoves()
    {
        switch(this->myRouter.GetFsm()->get_state_id()) {
            case FSM::MachineStateId::IDLE:
                break;
            case FSM::MachineStateId::ESTOP:
                break;
            case FSM::MachineStateId::MOVING: //still have to figure out if we're turning moving or threading moving
                GenerateTurningMoves();
                break;
            default:
                break;
        }
    }

    
} // namespace Machine::Planner