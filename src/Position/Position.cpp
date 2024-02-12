#include "Position/Position.hpp"

namespace Position
{

Position::Position()
{
    myPosition = 0; //consider restoring this on bootup.
}

void Position::Update()
{
    //update the internal position from the inheriting class (such as Encoder::Encoder or Encoder::EncoderSimulator)
    myPosition = UpdatePosition();
}

} // namespace Position