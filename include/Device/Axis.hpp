#pragma once

#include "Position/Position.hpp"
#include "Encoder/Encoder.hpp"

namespace Device 
{

class Axis : public Position::Position
{
    public:
        Axis(float aScaleFactor = 1.0f) : Position::Position(aScaleFactor) {};
        virtual void MoveTo(int32_t aTargetPosition) = 0;

        //Stop now, flushing any remaining motion commands, if possible.
        //If used with a closed loop stepper, this could turn off the enable pin. E-stop style.
        virtual void Stop() = 0;
};

} // namespace Device
