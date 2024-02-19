#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Position/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/Position/MockPosition.hpp"

class PositionGettersSettersTest : public DefaultUnitTest {
protected:
};

TEST_F(PositionGettersSettersTest, position_GetCountPeriod)
{
     MockPosition encoder;
     encoder.SetStatus({0, false, 0, 0, 0, false, 0, 0});

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(0, period);
}

TEST_F(PositionGettersSettersTest, position_GetPosition)
{
     MockPosition encoder;
     encoder.SetStatus({1000, false, 0, 0, 0, false, 0, 0});

     int32_t position = encoder.GetPosition();

     EXPECT_EQ(1000, position);

     encoder.SetStatus({1001, false, 0, 0, 0, false, 0, 0});

     position = encoder.GetPosition();

     EXPECT_EQ(1001, position);

}

TEST_F(PositionGettersSettersTest, position_GetMotionParams)
{
     MockPosition encoder;
     encoder.SetStatus({1000, false, 0, 0, 0, false, 0, 0});

     Position::Status status = encoder.GetMotionParams();

     EXPECT_EQ(1000, status.count);
     EXPECT_EQ(false, status.direction);
     EXPECT_EQ(0, status.timestamp);
     EXPECT_EQ(0, status.speed);
     EXPECT_EQ(0, status.lastCount);
     EXPECT_EQ(false, status.lastDirection);
     EXPECT_EQ(0, status.lastTimestamp);
     EXPECT_EQ(0, status.lastSpeed);

     encoder.SetStatus({1001, true, 1000, 1, 1000, true, 1000, 1});

     status = encoder.GetMotionParams();

     EXPECT_EQ(1001, status.count);
     EXPECT_EQ(true, status.direction);
     EXPECT_EQ(1000, status.timestamp);
     EXPECT_EQ(1, status.speed);
     EXPECT_EQ(1000, status.lastCount);
     EXPECT_EQ(true, status.lastDirection);
     EXPECT_EQ(1000, status.lastTimestamp);
     EXPECT_EQ(1, status.lastSpeed);

}

TEST_F(PositionGettersSettersTest, position_GetNormalizedPosition)
{
     MockPosition encoder(2.0f);
     encoder.SetStatus({1000, false, 0, 0, 0, false, 0, 0});

     int32_t position = encoder.GetNormalizedPosition();

     EXPECT_EQ(2000, position);

     encoder.SetStatus({2002, false, 0, 0, 0, false, 0, 0});

     position = encoder.GetNormalizedPosition();

     EXPECT_EQ(4004, position);

     MockPosition encoder2(0.5f);
     encoder2.SetStatus({1000, false, 0, 0, 0, false, 0, 0});
     position = encoder2.GetNormalizedPosition();
     EXPECT_EQ(500, position);

}

TEST_F(PositionGettersSettersTest, position_100msPerCountOver10Counts)
{
     Position::Status status = {0, false, 1000, 0, 0, false, 0, 0};
     status.count = 10;
     status.lastCount = 0;
     status.timestamp = 2000;
     status.lastTimestamp = 1000;

     MockPosition encoder;
     encoder.SetStatus(status);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(100, period);
}

TEST_F(PositionGettersSettersTest, position_GetStatus)
{
     Position::Status status = {0, false, 1000, 0, 0, false, 0, 0};
     Position::Status status2 = {1000, false, 1000, 0, 0, false, 0, 0};

     MockPosition encoder;
     encoder.SetStatus(status);

     Position::Status returnedStatus = encoder.GetStatus();

     EXPECT_EQ(status.count, returnedStatus.count);
     EXPECT_EQ(status.direction, returnedStatus.direction);
     EXPECT_EQ(status.timestamp, returnedStatus.timestamp);
     EXPECT_EQ(status.speed, returnedStatus.speed);
     EXPECT_EQ(status.lastCount, returnedStatus.lastCount);
     EXPECT_EQ(status.lastDirection, returnedStatus.lastDirection);
     EXPECT_EQ(status.lastTimestamp, returnedStatus.lastTimestamp);
     EXPECT_EQ(status.lastSpeed, returnedStatus.lastSpeed);

     encoder.SetStatus(status2);
     EXPECT_EQ(status2.count, encoder.GetStatus().count);
     EXPECT_NE(status.count, status2.count);


}