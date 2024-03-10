#pragma once

#include "state_base.hpp"

namespace Movement::Movement {

  /**
   * @brief Shallow History Pseudostates exist purely to re-implement
   *  the makeActive() function to actually call
   *  _parentState->setShallowHistory()
   */
  class ShallowHistoryState : public StateBase {
  public:
    using StateBase::StateBase;

    /**
     * @brief Calls _parentState->setShallowHistory().
     */
    void                      makeActive ( ) override {
      if (_parentState) {
        _parentState->setShallowHistory();
      }
    }
  };
} // namespace Movement
