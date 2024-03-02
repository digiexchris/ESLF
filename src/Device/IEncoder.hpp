#pragma once

#include "State/Position.hpp"

#include <etl/type_traits.h>

namespace Device
{

class IEncoder : public State::Position
{
    using State::Position::Position;
};

} // namespace Device