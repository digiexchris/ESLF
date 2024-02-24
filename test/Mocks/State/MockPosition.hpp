#pragma once

#include <trompeloeil.hpp>
#include "State/Position.hpp"
using namespace State;
class MockPosition : public State::Position {

public:
    //MockPosition(float aScaleFactor = 1.0f) : Position(aScaleFactor) {};
    MAKE_MOCK0(UpdateMotionParams, PositionParams&(), override);
    
};