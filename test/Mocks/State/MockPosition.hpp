#pragma once

#include <gmock/gmock.h>
#include "State/Position.hpp"
using namespace State;
class MockPosition : public State::Position {

public:
    //MockPosition(float aScaleFactor = 1.0f) : Position(aScaleFactor) {};
    MOCK_METHOD(PositionParams&, UpdateMotionParams, (), (override));
    
};