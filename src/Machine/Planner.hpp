#pragma once

#include "Device/Spindle.hpp"
#include "Device/IAxis.hpp"
#include "State/Position.hpp"
#include "Device/IEncoder.hpp"
#include <cstdarg>
#include <etl/vector.h>

namespace Machine
{
/**
The main sync state and motion functionality*/

//using State::Position = AxisEncoderType;

template <typename MainSpindleEncoder, size_t AxisCount, typename ...AxisType>
class Planner
{
    static_assert((Device::IsEncoder<MainSpindleEncoder>::value), "The spindle must inherit from IEncoder"); 
    static_assert((Device::IsAxis<AxisType>::value && ...), "The Axes must inherit from IAxis");

    public:
        Planner() 
        {
            
            myAxes.reserve(AxisCount);
            (myAxes.push_back(AxisType()), ...);
        }
        
        virtual void Update() = 0;
        virtual void GenerateMoves() = 0;

    protected:
        etl::vector<Device::IEncoder, AxisCount> myAxes
};

} // namespace Machine