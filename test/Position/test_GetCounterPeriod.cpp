#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Position/Position.hpp"
#include <stdint.h>
#include "DefaultUnitTest.hpp"
#include "Mocks/Position/MockPosition.hpp"

class GetCounterPeriodTest : public DefaultUnitTest {
protected:
};

TEST_F(GetCounterPeriodTest, spindle_stopped)
{
     MockPosition encoder;
     encoder.SetStatus({0, false, 0, 0, 0, false, 0, 0});

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(0, period);
}

TEST_F(GetCounterPeriodTest, 100ms_per_count_over_10_counts)
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