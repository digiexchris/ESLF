#include <trompeloeil.hpp>
#include "State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/State/MockPosition.hpp"
#include "catch2/catch_test_macros.hpp"

class PositionFunctionsTest : public DefaultUnitTest {
public:
    friend class MockPosition;
protected:
     MockPosition position;
};

TEST_CASE_METHOD(PositionFunctionsTest, "UpdateMotionParamsCalled", "[Position]")
{
    const State::PositionParams expectedPosition = {300, true, 1};    
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).RETURN(std::ref(expectedPosition));

    position.Update();
}

TEST_CASE_METHOD(PositionFunctionsTest, "Updated", "[Position]")
{
    const State::PositionParams expectedPosition1 = {300, true, 1};

    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).RETURN(std::ref(expectedPosition1));

    position.Update();

    REQUIRE(position.GetPosition() == 300);
    REQUIRE(position.GetDirection() == true);
    REQUIRE(position.GetTimestamp() == 1);
    
    const State::PositionParams expectedPosition2 = {400, false, 2};
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).RETURN(std::ref(expectedPosition2));
    position.Update();

    REQUIRE(position.GetPosition() == 400);
    REQUIRE(position.GetDirection() == false);
    REQUIRE(position.GetTimestamp() == 2);

}

TEST_CASE_METHOD(PositionFunctionsTest, "GreaterThan", "[Position]")
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 > pos2);
}

TEST_CASE_METHOD(PositionFunctionsTest, "LessThan", "[Position]")
{
    State::PositionParams params1 = {300, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 < pos2);
}

TEST_CASE_METHOD(PositionFunctionsTest, "Equal", "[Position]")
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 == pos2);
}

TEST_CASE_METHOD(PositionFunctionsTest, "Diff", "[Position]")
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 - pos2 == 100);

    REQUIRE(pos2 + pos1 == 700);
}