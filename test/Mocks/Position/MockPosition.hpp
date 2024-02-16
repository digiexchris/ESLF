#pragma once

#include <gmock/gmock.h>
#include "Position/Position.hpp"

class MockPosition : public Position {

public:
    MockPosition(float aScaleFactor = 1.0f) : Position(aScaleFactor) {};
    MOCK_METHOD(Status, UpdateMotionParams, (), (override));
    
};