#pragma once

#include <cstdint>
#include <etl/atomic.h>

class Position 
{
public:

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

    /** @brief Set the default 0 position, with an optional scale factor
    * Note: Ideally to avoid losing precision as much as possible, choose a scale factor
    * that will result in a normalized position that is an integer.
    */
    Position(float aScaleFactor = 1.0f) : myScaleFactor(aScaleFactor) 
    {
        myStatus = {0, false, 0, 0, 0, false, 0, 0};
    };

    /**
    * @brief Update the internal position.
    * 
    * This function should be called by the main position correction loop on a regular basis.
    * 
    */
    virtual void Update() {
        myStatus.store(UpdateMotionParams());
        myStatus = UpdateMotionParams();
    };
    
    int32_t GetPosition() const { 
        Status s = myStatus.load();
        return s.count;
    }

    void SetStatus(Status aStatus) {
        myStatus.store(aStatus);
    }


    int32_t GetNormalizedPosition() const { 
        Status s = myStatus.load();
        return s.count * myScaleFactor; 
    } 

    /**
     * @brief Returns the average time between counts in milliseconds.
     * 
     * @return The average time between counts as a uint16_t value.
     * If the period is zero, the encoder has not moved since the last update.

     intended to be used if you're using a timer based stepper, instead of a closed loop servo
     */
    virtual uint16_t GetCountPeriod() final;

    virtual Status GetMotionParams() final;


protected:
    
    /**
     * @brief Gets the position, direction, speed, etc. of the encoder.
     * 
     * @note it's recommended to do as much as possible with a single read of this
     * since it's backed by std::atomic and is more expensive than reading individual
     * ints, but guarantees the timestamps, speed, and direction are consistent.
     * 
     * @return The position, direction, speed, etc. of the encoder as a Status struct.
     */
     virtual Status UpdateMotionParams() = 0;

    etl::atomic<Status> myStatus;   ///< The current and previous position, speed and direction of the encoder.

    //the scaling factor back to the main position
    float myScaleFactor;

};
