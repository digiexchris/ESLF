#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/State/MockPosition.hpp"

class PositionGettersSettersTest : public DefaultUnitTest {
protected:
};

TEST_F(PositionGettersSettersTest, position_GetPosition)
{
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     int32_t position = encoder.GetPosition();

     EXPECT_EQ(1000, position);

     encoder.Set({1001, false, 0});

     position = encoder.GetPosition();

     EXPECT_EQ(1001, position);

}

TEST_F(PositionGettersSettersTest, position_GetDirection)
{
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     bool direction = encoder.GetDirection();

     EXPECT_EQ(false, direction);

     encoder.Set({1001, true, 0});

     direction = encoder.GetDirection();

     EXPECT_EQ(true, direction);

}

TEST_F(PositionGettersSettersTest, position_GetTimestamp)
{
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     uint32_t timestamp = encoder.GetTimestamp();

     EXPECT_EQ(0, timestamp);

     encoder.Set({1001, false, 1000});

     timestamp = encoder.GetTimestamp();

     EXPECT_EQ(1000, timestamp);

}

TEST_F(PositionGettersSettersTest, position_GetNormalizedPosition)
{
     MockPosition encoder;
     
     encoder.SetScaleFactor(2);
     encoder.Set({1000, false, 0});

     EXPECT_EQ(2000, encoder.GetPosition());
     encoder.Set({1001, false, 1000});
     EXPECT_EQ(2002, encoder.GetPosition());

     MockPosition encoder2;
     encoder2.SetScaleFactor(0.5);
     encoder2.Set({1000, false, 0});

     EXPECT_EQ(500, encoder2.GetPosition());
     encoder2.Set({1001, false, 1000});
     EXPECT_EQ(500, encoder2.GetPosition());
     encoder2.Set({1002, false, 1000});
     EXPECT_EQ(501, encoder2.GetPosition());
     encoder2.Set({1003, false, 1000});
     EXPECT_EQ(501, encoder2.GetPosition());
     encoder2.Set({1004, false, 1000});
     EXPECT_EQ(502, encoder2.GetPosition());
}

TEST_F(PositionGettersSettersTest, position_100msPerCountOver10Counts)
{
     MockPosition encoder;
     State::PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(100, period);
}

TEST_F(PositionGettersSettersTest, position_100msPerCountOver10CountsNormalized)
{
     MockPosition encoder;
     encoder.SetScaleFactor(0.5);
     State::PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(200, period);
}

TEST_F(PositionGettersSettersTest, position_GetCountPeriod_WhenNotMoving)
{
     MockPosition encoder;
     encoder.SetScaleFactor(2);
     State::PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(50, period);
     params = {10, false, 4000};
     
     encoder.Set(params);

     period = encoder.GetCountPeriod();
     EXPECT_EQ(0, period);


}

//TODO write a test validating the carry over longer iterations