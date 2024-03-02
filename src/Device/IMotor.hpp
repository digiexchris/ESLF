#pragma once
#include "State/Position.hpp"
#include <cstdint>
#include <etl/type_traits.h>

namespace Device
{

class IMotor : public State::Position
{
    public:
        explicit IMotor(float aNormalizedScaleFactor) : State::Position(aNormalizedScaleFactor) {};

        //Move to a target position, if possible.
        virtual void MoveTo(int32_t aTargetPosition) = 0;

        //Stop now, flushing any remaining motion commands, if possible.
        //If used with a closed loop stepper, this could turn off the enable pin. E-stop style.
        virtual void Stop() = 0;

        
};

// Traits to check if a type used in a template can be used as a motor
template<typename T, typename = void>
struct IsMotor : etl::false_type {};

template<typename T>
struct IsMotor<T,  etl::void_t<decltype( etl::declval<T>().MoveTo())>> :  etl::true_type {};

} // namespace Device