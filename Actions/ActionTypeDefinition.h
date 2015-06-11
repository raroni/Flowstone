#ifndef ACTIONS_ACTION_TYPE_DEFINITION_H
#define ACTIONS_ACTION_TYPE_DEFINITION_H

#include <stdint.h>

namespace Actions {
  class ActionTypeDefinition {
  public:
    void reset();
    uint8_t instanceMax;
    uint8_t paramLength;
    uint8_t configLength;
    uint8_t stateLength;
  };
}

#endif
