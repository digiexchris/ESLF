#pragma once
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
            Device::Axis<ZAxisMotor>& anAxis);

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
            Device::Axis<ZAxisMotor>& anAxis) 
            : Planner<MainSpindleEncoder>(aMainSpindle),
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
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateMoves()
    {
        switch(this->get_state_id()) {
            case FSM::MachineStateId::IDLE:
                break;
            case FSM::MachineStateId::ESTOP:
                break;
            case FSM::MachineStateId::MOVING: //TODO figure out if we're turning moving or threading moving
                GenerateTurningMoves();
                break;
            default:
                break;
        }
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateTurningMoves()
    {

        if(myZAxis != this->myMainSpindleEncoder)
        {
            //NOTE: both positions should be ints at this point, scaled internally
            //TODO this is a 1:1 ratio, no gearing.
            myZAxis.Move(myZAxis.Diff(this->myMainSpindleEncoder));
        }

    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void Planner1<MainSpindleEncoder, ZAxisMotor>::GenerateThreadingMoves()
    {
        //if(get_child_state_id() != FSM::MachineStateId::RUNNING)
        // {
        //     if(myZAxis != this->myMainSpindleEncoder)
        //     {
                    
        //     }
        // }
    }
} // namespace Machine::Planner