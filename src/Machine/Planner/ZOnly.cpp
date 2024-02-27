#include "ZOnly.hpp"


namespace Machine
{
namespace Planner
{
    template <typename MainSpindleEncoder, typename ZAxisMotor>
    ZOnly<MainSpindleEncoder, ZAxisMotor>::ZOnly(
            MainSpindleEncoder& aMainSpindle, 
            Device::Axis<ZAxisMotor>& anAxis) 
            : Planner<MainSpindleEncoder>(aMainSpindle),
            myZAxis(anAxis)
        {
        }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void ZOnly<MainSpindleEncoder, ZAxisMotor>::Update()
    {
        // Update the main spindle encoder
        this->myMainSpindleEncoder.Update();
        myZAxis.Update();
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void ZOnly<MainSpindleEncoder, ZAxisMotor>::GenerateMoves()
    {
        switch(this->get_state_id()) {
            case FSM::MachineStateId::IDLE:
                break;
            case FSM::MachineStateId::ESTOP:
                break;
            case FSM::MachineStateId::TURNING:
                GenerateTurningMoves();
                break;
            // case FSM::MachineStateId::THREADING:
            //     GenerateThreadingMoves();
            //     break;
            default:
                break;
        }
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void ZOnly<MainSpindleEncoder, ZAxisMotor>::GenerateTurningMoves()
    {
        //if(get_child_state_id() != FSM::MachineStateId::RUNNING)
        {
            if(myZAxis != this->myMainSpindleEncoder)
            {
                    
            }
        }
    }

    template <typename MainSpindleEncoder, typename ZAxisMotor>
    void ZOnly<MainSpindleEncoder, ZAxisMotor>::GenerateThreadingMoves()
    {
        //if(get_child_state_id() != FSM::MachineStateId::RUNNING)
        {
            if(myZAxis != this->myMainSpindleEncoder)
            {
                    
            }
        }
    }
} // namespace Planner
} // namespace Machine