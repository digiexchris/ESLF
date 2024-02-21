#include "Device/EncoderSimulator.hpp"
#include "State/Position.hpp"
#include "State/Position.hpp"

namespace Device
{
    using State::PositionParams;

    EncoderSimulator::EncoderSimulator(float aNormalizedScaleFactor) : State::Position(aNormalizedScaleFactor)
    {
        myParams = {0, false, 0};
    }

    PositionParams& EncoderSimulator::UpdateMotionParams()
    {
        mySimulatedCount++;
        mySimulatedTimestamp += 10;
        myParams = {mySimulatedCount, false, mySimulatedTimestamp};
        return myParams;
    }
} // namespace Device