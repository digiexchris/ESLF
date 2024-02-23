#include "VirtualMotor.hpp"

namespace Device
{
    VirtualMotor::VirtualMotor(float aNormalizedScaleFactor) : IMotor(aNormalizedScaleFactor)
    {
        
    }

    PositionParams& VirtualMotor::UpdateMotionParams()
    {
        if(myTargetPosition != myParams.count)
        {
            if(myTargetPosition > myParams.count)
            {
                myParams.direction = true;
                myParams.count++;
            }
            else
            {
                myParams.direction = false;
                myParams.count--;
            }
        }
        else 
        {
            //TODO this is where you'd adjust the internal state machine to say this axis is in position. Maybe
            //call a virtual on the base class to send a message.
            //this behaviour probably isn't needed. Motors need to always try to stay in sync unless they're off.
        }
       
        return myParams;
    }
} // namespace Device