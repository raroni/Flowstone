#ifndef ACTIONS_NODE_FLOW_H
#define ACTIONS_NODE_FLOW_H

#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStateIndex.h"
#include "Actions/NodeIndex.h"

namespace Actions {
  class NodeFlow {
  public:
    NodeFlow(ActionTypeIndex typeIndex, ActionStateIndex stateIndex);
    void start(NodeIndex nodeIndex);
    const void* getConfig() const;
    void* getState();
  private:
    const void *config;
    void *state;
    ActionTypeIndex actionTypeIndex;
    ActionStateIndex actionStateIndex;
  };
}

#endif
