#ifndef ACTIONS_STATE_COLLECTION_H
#define ACTIONS_STATE_COLLECTION_H

#include "Actions/ActionStateHandle.h"
#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStateIndex.h"

namespace Actions {
  namespace StateCollection {
    ActionStateHandle createInstance(ActionTypeIndex index);
    void createList(ActionTypeIndex index);
    void* get(ActionTypeIndex typeIndex, ActionStateIndex stateIndex);
    ActionStateIndex getIndex(ActionTypeIndex typeIndex, ActionStateHandle stateHandle);
  }
}

#endif
