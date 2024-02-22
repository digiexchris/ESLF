#pragma once

#include "State/Position.hpp"
#include "Device/IEncoder.hpp"

namespace Device 
{

template <typename EncoderType>
class IAxis : public EncoderType
{
    static_assert((Device::IsEncoder<EncoderType>::value), "All Axis must inherit from IEncoder, even if it's just a VirtualMotorEncoder that never gets updated.");
    public:
        Axis(float aScaleFactor = 1.0f) : State::Position(aScaleFactor) {};
        virtual void MoveTo(int32_t aTargetPosition) = 0;

        //Stop now, flushing any remaining motion commands, if possible.
        //If used with a closed loop stepper, this could turn off the enable pin. E-stop style.
        virtual void Stop() = 0;
};

// Traits to check if a type used in a template can be used as an encoder
template<typename T, typename = void>
struct IsAxis : etl::false_type {};

template<typename T>
struct IsAxis<T,  etl::void_t<decltype( etl::declval<T>().MoveTo())>> :  etl::true_type {};

} // namespace Device
