#ifndef ACTIONS_ACTION_TYPE_LIST_H
#define ACTIONS_ACTION_TYPE_LIST_H

#include "Actions/ActionTypeDefinition.h"
#include "Actions/ActionTypeIndex.h"

namespace Actions {
  namespace ActionTypeList {
    ActionTypeIndex create(const ActionTypeDefinition *definition);
    uint8_t getParamLength(ActionTypeIndex index);
    uint8_t getStateLength(ActionTypeIndex index);
    uint8_t getInstanceMax(ActionTypeIndex index);
  }
}

#endif
