#pragma once

#include "State/Position.hpp"
#include "Device/IEncoder.hpp"
#include "Device/IMotor.hpp"

namespace Device 
{

template <typename EncoderType, typename MotorType>
class Axis : public EncoderType
{
    static_assert((Device::IsMotor<MotorType>::value), "All Axis MotorTypes must inherit from IMotor.");
    static_assert((Device::IsEncoder<EncoderType>::value), "All Axis EncoderTypes must inherit from IEncoder, even if it's just a VirtualEncoder that never gets updated.");
    public:
        Axis(EncoderType& anEncoder, MotorType& aMotor) : myMotor(aMotor), myEncoder(anEncoder)
        {
        }
    protected:
        MotorType& myMotor;
        EncoderType& myEncoder;

        //just for the type trait below
        void PrivIsAxis() {};
};

// Traits to check if a type used in a template can be used as an encoder
template<typename T, typename = void>
struct IsAxis : etl::false_type {};

template<typename T>
struct IsAxis<T,  etl::void_t<decltype( etl::declval<T>().PrivIsAxis())>> :  etl::true_type {};

} // namespace Device
