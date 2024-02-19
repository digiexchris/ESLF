#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Position/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/Position/MockPosition.hpp"

class PositionFunctionsTest : public DefaultUnitTest {
protected:
     MockPosition position;
};

TEST_F(PositionFunctionsTest, UpdateMotionParamsCalled)
{
    EXPECT_CALL(position, UpdateMotionParams()).Times(1);

    position.Update();
}

TEST_F(PositionFunctionsTest, StatusUpdated)
{
    Position::Status expectedStatus = {300, true, 1, 2, 3, true, 4, 5};

    EXPECT_CALL(position, UpdateMotionParams()).WillOnce(::testing::Return(expectedStatus));

    position.Update();

    //EXPECT_EQ(expectedStatus, position.GetStatus());
}