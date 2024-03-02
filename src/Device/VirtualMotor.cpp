#include "VirtualMotor.hpp"

namespace Device
{
    VirtualMotor::VirtualMotor(float aNormalizedScaleFactor) : IMotor(aNormalizedScaleFactor)
    {
        
    }

    void VirtualMotor::MoveTo(int32_t aTargetPosition)
    {
        myParams.count = aTargetPosition;
        Update();
    }

    void VirtualMotor::Stop()
    {
        //noop
    }

    PositionParams& VirtualMotor::UpdateMotionParams()
    {
        return myParams;
    }
} // namespace Device