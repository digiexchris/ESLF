#pragma once
#include "State/Position.hpp"
#include "IEncoder.hpp"

namespace Device
{

using State::PositionParams;
/**
* @brief A virtual encoder for motors with no encoder of their own.
* Basically just reports the same position the motor was asked to move to
* at the end of it's move (in the case of a dumb motor) or when it was asked to (in the case of a closed loop)
* or some other implementation (motor implementation dependent of course, these are hypotheticals)
* Can also be used for 1 axis machines, this could be the other axis and just don't update it's position.*/
class VirtualMotorEncoder : public IEncoder
{
    public:
        VirtualMotorEncoder(float aNormalizedScaleFactor = 1.0);
        void SetPosition(int32_t aPosition);
    protected:
        PositionParams& myParams;

        //basically just returning the stored internal state. The motor update loop will update this internal state.
        virtual PositionParams& UpdateMotionParams() override;
}; // class VirtualMotorEncoder


} // namespace Device
