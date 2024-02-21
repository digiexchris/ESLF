#pragma once

#include "State/Position.hpp"

namespace Device
{
//*
// * @brief Spindle class
// *Example Encoder Type: Spindle<EncoderSimulator>
// */
template <typename EncoderType>
class Spindle : public EncoderType
{
    public:

    protected:
};
} // namespace Spindle