#include <gtest/gtest.h>
#include "Encoder/IEncoder.hpp"
#include <stdint.h>
#include "DefaultUnitTest.hpp"

class MockEncoder : public Encoder {
     public:
          void Update() override {}

          void SetStatus(Status status) {
               myStatus.store(status);
          }
};

class EncoderGetCounterPeriodTest : public DefaultUnitTest {
protected:
};

TEST_F(EncoderGetCounterPeriodTest, spindle_stopped)
{
     MockEncoder encoder;
     encoder.SetStatus({0, false, 0, 0, 0, false, 0, 0});

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(0, period);
     //zassert_equal(256, fixture->max_size);
}

TEST_F(EncoderGetCounterPeriodTest, 100ms_per_count_over_10_counts)
{
     Encoder::Status status = {0, false, 1000, 0, 0, false, 0, 0};
     status.count = 10;
     status.lastCount = 0;
     status.timestamp = 2000;
     status.lastTimestamp = 1000;

     MockEncoder encoder;
     encoder.SetStatus(status);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(100, period);
}