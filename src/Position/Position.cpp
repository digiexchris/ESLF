#include "Position/Position.hpp"

#include <etl/absolute.h>
#include <etl/atomic.h>
#include <Logging/Logger.hpp>

Position::Position(float aScaleFactor ) : myScaleFactor(aScaleFactor) 
{
    myStatus = {0, false, 0, 0, 0, false, 0, 0};
};

void Position::Update() {
    myStatus.store(UpdateMotionParams());
};

int32_t Position::GetPosition() const { 
    Status s = myStatus.load();
    return s.count;
}

Position::Status Position::GetStatus() const {
    return myStatus.load();
}

void Position::SetStatus(Status aStatus) {
    myStatus.store(aStatus);
}

int32_t Position::GetNormalizedPosition() const { 
    Status s = myStatus.load();
    return s.count * myScaleFactor; 
} 

uint16_t Position::GetCountPeriod() 
{
    Status status = myStatus.load();
    uint16_t timeDifference = status.timestamp - status.lastTimestamp;
    int32_t countDifference = etl::absolute(static_cast<int32_t>(status.count) - static_cast<int32_t>(status.lastCount));

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
