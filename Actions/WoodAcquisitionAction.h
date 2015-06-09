#ifndef ACTIONS_WOOD_ACQUISITION_ACTION_H
#define ACTIONS_WOOD_ACQUISITION_ACTION_H

#include <stdint.h>

namespace Actions {
  namespace WoodAcquisitionAction {
    extern uint8_t instanceMax;
    extern uint8_t configLength;
    extern uint8_t stateLength;
    extern uint8_t paramLength;
    void start(void *state);
  }
}

#endif
