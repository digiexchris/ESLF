#pragma once

#include "State/Position.hpp"
#include "Device/IEncoder.hpp"
#include "Device/IMotor.hpp"
#include <cstdarg>
#include <etl/utility.h>

namespace Device 
{

template <typename MotorType>
class Axis : public MotorType
{
    // static_assert((Device::IsMotor<MotorType>::value), "All Axis MotorTypes must inherit from IMotor.");
    // static_assert((Device::IsEncoder<EncoderType>::value), "All Axis EncoderTypes must inherit from IEncoder, even if it's just a VirtualEncoder that never gets updated.");
    public:
        template <typename... MotorTypeArgs>
        Axis(const char anId, MotorTypeArgs&&... args): myId(anId), MotorType(etl::forward<MotorTypeArgs>(args)...) {
        };
    protected:
        char myId;

        //just for the type trait below
        void PrivIsAxis() {};
        const char GetId() { return myId; };
};

// Traits to check if a type used in a template can be used as an encoder
template<typename T, typename = void>
struct IsAxis : etl::false_type {};

template<typename T>
struct IsAxis<T,  etl::void_t<decltype( etl::declval<T>().PrivIsAxis())>> :  etl::true_type {};

} // namespace Device
