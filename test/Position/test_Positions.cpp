#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/State/MockPosition.hpp"

class PositionFunctionsTest : public DefaultUnitTest {
public:
    friend class MockPosition;
protected:
     MockPosition position;
};

TEST_F(PositionFunctionsTest, UpdateMotionParamsCalled)
{
    State::PositionParams expectedPosition = {300, true, 1};    
    EXPECT_CALL(position, UpdateMotionParams()).Times(1).WillOnce(::testing::ReturnRef(expectedPosition));

    position.Update();
}

TEST_F(PositionFunctionsTest, Updated)
{
    State::PositionParams expectedPosition = {300, true, 1};

    EXPECT_CALL(position, UpdateMotionParams())
        .WillOnce(::testing::ReturnRef(expectedPosition));

    position.Update();

    EXPECT_EQ(position.GetPosition(), 300);
    EXPECT_EQ(position.GetDirection(), true);
    EXPECT_EQ(position.GetTimestamp(), 1);
    
    expectedPosition = {400, false, 2};
    EXPECT_CALL(position, UpdateMotionParams()).WillOnce(::testing::ReturnRef(expectedPosition));
    position.Update();

    EXPECT_EQ(position.GetPosition(), 400);
    EXPECT_EQ(position.GetDirection(), false);
    EXPECT_EQ(position.GetTimestamp(), 2);

}

TEST_F(PositionFunctionsTest, GreaterThan)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_TRUE(pos1 > pos2);
}

TEST_F(PositionFunctionsTest, LessThan)
{
    State::PositionParams params1 = {300, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_TRUE(pos1 < pos2);
}

TEST_F(PositionFunctionsTest, Equal)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_TRUE(pos1 == pos2);
}

TEST_F(PositionFunctionsTest, Diff)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_EQ(pos1 - pos2, 100);

    EXPECT_EQ(pos2 + pos1, 700);
}