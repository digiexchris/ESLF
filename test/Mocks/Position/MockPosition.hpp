#pragma once

#include <gmock/gmock.h>
#include "Position/Position.hpp"

class MockPosition : public Position {

public:
    MOCK_METHOD(Status, UpdateMotionParams, (), (override));
    
};