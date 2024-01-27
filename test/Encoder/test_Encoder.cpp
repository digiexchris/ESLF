#include <gtest/gtest.h>
#include "../../include/Encoder/IEncoder.hpp"
#include <stdint.h>


class MockEncoder : public Encoder {
     public:
          void Update() override {}

          void SetStatus(Status status) {
               myStatus.store(status);
          }
};

/*
struct Status {
        int32_t count;
        bool direction;
        uint32_t timestamp;
        uint16_t speed;
        uint32_t lastCount;
        bool lastDirection;
        uint32_t lastTimestamp;
        uint16_t lastSpeed;
    };
*/

TEST(get_counter_period, spindle_stopped)
{
     MockEncoder encoder;
     encoder.SetStatus({0, false, 0, 0, 0, false, 0, 0});

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_EQ(0, period);
     //zassert_equal(256, fixture->max_size);
}

TEST(get_counter_period, 100ms_per_count_over_10_counts)
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