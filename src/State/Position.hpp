#pragma once

#include <cstdint>

/**
*/
namespace State
{

struct PositionParams
{
    int32_t count;
    bool direction;
    uint32_t timestamp;
};

class Position 
{
public:

    

    /** @brief Set the default 0 position, with an optional scale factor
    * Note: Ideally to avoid losing precision as much as possible, choose a scale factor
    * that will result in a normalized position that is an integer.
    */
    Position(float aNormalizedScaleFactor = 1.0f);

    /**
    * @brief Update the internal position.
    * 
    * This function should be called by the main position correction loop on a regular basis.
    * Since we want to generally deal in integers, this position needs to be normalized to the main position, and keep
    * track of the rounded parts of the position to be applied next update.
    */
    virtual void Update() ;
    
    //normalized, rounding errors internally managed
    int32_t GetPosition() const;
    bool GetDirection() const;
    uint32_t GetTimestamp() const;
  
    void Set(PositionParams aParams);

    //this one is mostly used just for setting up the initial coordinate space (reference to the main position)
    //eg. if the main position is 4096, and the spindle encoder is 2048, then the normalized scale factor is 2
    void SetScaleFactor(float myScaleFactor);

    
    //return the difference between this position and another position, taking all scaling and ratio factors into account
    //ie. how far ahead or behind the other potsition (eg. the main position)
    //the diff should return an int, not the rounded portions. If we're moving constantly, the next diff will incorporate some or all of the rounded portion.
    int32_t Diff(const Position& aPosition) const;

    /**
     * @brief Returns the average time between counts in milliseconds.
     * 
     * @return The average time between counts as a uint16_t value.
     * If the period is zero, the encoder has not moved since the last update.

     intended to be used if you're using a timer based stepper, instead of a closed loop servo
     since it's intended to be used internally, it's not noralized.
     */
    virtual uint16_t GetCountPeriod() const final;

    virtual bool operator>(const Position& aPosition) const;
    virtual bool operator<(const Position& aPosition) const;
    virtual bool operator==(const Position& aPosition) const;
    virtual int32_t operator-(const Position& aPosition) const;
    virtual int32_t operator+(const Position& aPosition) const;

protected:
    
    /**
     * @brief Gets the position, direction, speed, etc. of the encoder.
     * 
     * @return The position, direction, speed, etc. of the encoder as a PositionParams struct.
     */
    virtual PositionParams& UpdateMotionParams() = 0;

    //normalized
    int32_t myCount;

    //in the encoder's scale
    int32_t myRawCount;

    //in the nencoder's scale. The number left over from translating it to the normalized position
    int16_t myCarry;

    //when the position is output, it will be multiplied by this to get the position back to the main position
    float myScaleFactor;

    bool myDirection;
    uint32_t myTimestamp;
    uint32_t myLastRawCount;
    bool myLastDirection;
    uint32_t myLastTimestamp;

};

} // namespace Position