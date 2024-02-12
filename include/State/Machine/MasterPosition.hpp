#pragma once

#include "Position/Position.hpp"
#include <cstdint>

namespace State::Machine
{

/** @brief The system's master position
*
* All other positions are scaled internally to this one
* This expects all positions to be in the the same scale
* and will output the delta in the same scale
*/
template <typename ...T>
class MasterPosition : public Position::Position
{
    public:
    
        /** @brief Get the delta between the target position and the current position
        * an example target could be the spindle encoder, and the current is the motor encoder.
        */
        void GetPositionDelta();

        /** @brief Set the scale of the master position in positions per revolution
        *
        */
        uint32_t GetScale();
};

} // namespace State::Machine