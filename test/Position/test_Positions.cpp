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

TEST_F(PositionFunctionsTest, GreaterThan)
{
    Position::Status status1 = {400, true, 1, 2, 3, true, 4, 5};
    MockPosition pos1;
    pos1.SetStatus(status1);
    Position::Status status2 = {300, true, 1, 2, 3, true, 4, 5};
    MockPosition pos2;
    pos2.SetStatus(status2);



    EXPECT_TRUE(pos1 > pos2);
}

TEST_F(PositionFunctionsTest, LessThan)
{
    Position::Status status1 = {300, true, 1, 2, 3, true, 4, 5};
    MockPosition pos1;
    pos1.SetStatus(status1);
    Position::Status status2 = {500, true, 1, 2, 3, true, 4, 5};
    MockPosition pos2;
    pos2.SetStatus(status2);

    EXPECT_TRUE(pos1 < pos2);
}

TEST_F(PositionFunctionsTest, Equal)
{
    Position::Status status1 = {300, true, 1, 2, 3, true, 4, 5};
    MockPosition pos1;
    pos1.SetStatus(status1);
    Position::Status status2 = {300, true, 1, 2, 3, true, 4, 5};
    MockPosition pos2;
    pos2.SetStatus(status2);

    EXPECT_TRUE(pos1 == pos2);
}