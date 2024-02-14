#include "Position/Position.hpp"

#include <etl/absolute.h>
#include <etl/atomic.h>
#include <Logging/Logger.hpp>

uint16_t Position::GetCountPeriod() {
    Status status = myStatus.load();
    uint16_t timeDifference = status.timestamp - status.lastTimestamp;
    int32_t countDifference = etl::absolute(static_cast<int32_t>(status.count) - static_cast<int32_t>(status.lastCount));
ELSF_LOG_INFO("Something");
    // Check if countDifference is not zero to avoid division by zero
    if (countDifference != 0) {
        uint16_t averageTimeBetweenCounts = timeDifference / countDifference;
        return averageTimeBetweenCounts;
    } else {
        return 0;
    }
}

Position::Status Position::GetMotionParams() {
    return myStatus.load();
}
