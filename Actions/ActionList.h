#ifndef ACTIONS_ACTION_LIST_H
#define ACTIONS_ACTION_LIST_H

#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStartFunction.h"

namespace Actions {
  namespace ActionList {
    ActionTypeIndex create(
      uint8_t paramLength,
      uint8_t instanceMax,
      uint8_t stateLength,
      ActionStartFunction startFunc
    );

    ActionStartFunction getStart(ActionTypeIndex index);
    uint8_t getParamLength(ActionTypeIndex index);
    uint8_t getStateLength(ActionTypeIndex index);
    uint8_t getInstanceMax(ActionTypeIndex index);
  }
}

#endif
