#pragma once

namespace Position
{


class Position 
{
public:
    Position();


    /**
    * @brief Update the internal position.
    * 
    * This function should be called by the main position correction loop on a regular basis.
    */
    void Update();
    
    long long GetPosition() const { return myPosition; }

protected:

    virtual long long UpdatePosition() = 0;
    //The position of this device, with this device's resolution (not scaled)
    long long myPosition;

};

} // namespace Position