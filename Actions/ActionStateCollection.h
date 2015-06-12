#ifndef ACTIONS_ACTION_STATE_COLLECTION_H
#define ACTIONS_ACTION_STATE_COLLECTION_H

#include "Actions/ActionStateHandle.h"
#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStateIndex.h"

namespace Actions {
  namespace ActionStateCollection {
    ActionStateHandle createInstance(ActionTypeIndex index);
    void createList(ActionTypeIndex index);
    void* getNodeState(ActionTypeIndex typeIndex, ActionStateIndex stateIndex, NodeIndex nodeIndex);
    ActionStateIndex getIndex(ActionTypeIndex typeIndex, ActionStateHandle stateHandle);
  }
}

#endif
