#include "VirtualEncoder.hpp"
#include "State/Position.hpp"

namespace Device
{
    using State::PositionParams;

    VirtualEncoder::VirtualEncoder(float aNormalizedScaleFactor) : IEncoder(aNormalizedScaleFactor)
    {
        myParams = {0, false, 0};
    }

    void VirtualEncoder::SetCountIncrement(int32_t aCountIncrement)
    {
        mySimulatedIncrement = aCountIncrement;
    }

    void VirtualEncoder::SetDirection(bool aDirection)
    {
        mySimulatedDirection = aDirection;
    }

    PositionParams& VirtualEncoder::UpdateMotionParams()
    {
        mySimulatedCount += mySimulatedIncrement;
        mySimulatedTimestamp += 10;
        myParams = {mySimulatedCount, mySimulatedDirection, mySimulatedTimestamp};
        return myParams;
    }
} // namespace Device