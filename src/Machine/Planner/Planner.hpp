#pragma once

#include "Device/Axis.hpp"
#include "State/Position.hpp"
#include "Device/IEncoder.hpp"
#include <cstdarg>
#include <etl/vector.h>
#include "Machine/FSM/Machine.hpp"

namespace Machine
{
namespace Planner
{
/**
The main sync state and motion functionality*/

template <typename MainSpindleEncoder>
class Planner: public Machine::FSM::MachineFSM
{
    //static_assert((Device::IsEncoder<MainSpindleEncoder>::value), "The planner template type MainSpindleEncoder must derive from IEncoder"); 

    public:
        Planner(MainSpindleEncoder& aMainSpindleEncoder) : myMainSpindleEncoder(aMainSpindleEncoder)
        {}
        virtual void Update() = 0;
        virtual void GenerateMoves() = 0;

    protected:
        MainSpindleEncoder& myMainSpindleEncoder;
};



}} // namespace Machine::Planner