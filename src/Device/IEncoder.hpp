#pragma once

#include "State/Position.hpp"

#include <etl/type_traits.h>

namespace Device
{

class IEncoder : public State::Position
{
    public:
        explicit IEncoder(float aNormalizedScaleFactor = 1.0f) : State::Position(aNormalizedScaleFactor){

        };
        virtual ~IEncoder() = default; // Ensure proper destruction of derived classes
};

} // namespace Device