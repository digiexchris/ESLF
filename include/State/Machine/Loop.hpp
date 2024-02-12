#pragma once

namespace State::Machine {

class ControlLoop
{
public:
    ControlLoop(int periodInMs);

    /**
    * @brief Update the internal position.
    * 
    * This function should be called by the main position correction loop on a regular basis.
    */
    void Update();

};

} // namespace State::Machine