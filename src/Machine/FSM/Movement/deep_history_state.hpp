#pragma once

#include "state_base.hpp"

namespace Movement::Movement {

  /**
   * @brief Deep History Pseudostates exist purely to re-implement the
   *  makeActive() function to actually call
   *  _parentState->setDeepHistory()
   */
  class DeepHistoryState : public StateBase {
  public:
  
    using StateBase::StateBase;

    /**
     * @brief Calls _parentState->setDeepHistory()
     */
    void                      makeActive ( ) override {
      if (_parentState) {
        _parentState->setDeepHistory();
      }
    }
  };
} // namespace Movement
