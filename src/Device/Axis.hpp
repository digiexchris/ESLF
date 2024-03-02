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
    public:
        template <typename... MotorTypeArgs>
        Axis(const char anId, MotorTypeArgs&&... args): myId(anId), MotorType(etl::forward<MotorTypeArgs>(args)...) {
        };
    protected:
        
        char GetId() { return myId; };

    private:
        char myId;
};

} // namespace Device
