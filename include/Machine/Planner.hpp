#pragma once

#include "Device/Spindle.hpp"
#include "Device/Axis.hpp"

namespace Machine
{
/**
The main sync state and motion functionality*/
class Planner 
{

};

template <typename SpindleEncoderType, typename ZAxisEncoderType, typename XAxisEncoderType>
class LathePlanner : public Planner
{

    protected:
        Device::Spindle<SpindleEncoderType> spindle;
        Device::Axis<ZAxisEncoderType> myZAxis;
        Device::Axis<XAxisEncoderType> myXAxis;
};

} // namespace Machine