#pragma once
#include "State/Position.hpp"
#include "IEncoder.hpp"

namespace Device
{
using State::PositionParams;

/**
 * @brief An encoder simulator. Increments the count and time every time UpdateMotionParams is called*/
 //TODO figure out a platform agnostic way of getting an RTOS/thread equivalent tick for use as a timestamp.
class EncoderSimulator : public IEncoder<EncoderSimulator>
{
    public:
        EncoderSimulator(float aNormalizedScaleFactor = 1.0);
        void SetCountIncrement(int32_t aCountIncrement);
        void SetDirection(bool aDirection);

    protected:
        PositionParams myParams;
        virtual PositionParams& UpdateMotionParams() override;
        int32_t mySimulatedCount;
        uint32_t mySimulatedTimestamp;
        bool mySimulatedDirection;
};
} // namespace Device