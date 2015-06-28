#ifndef ACTIONS_NODE_FLOW_H
#define ACTIONS_NODE_FLOW_H

#include "Database/EntityHandle.h"
#include "Actions/NodeTypeIndex.h"
#include "Actions/ActionTypeIndex.h"
#include "Actions/ActionStateIndex.h"
#include "Actions/NodeIndex.h"

namespace Actions {
  class NodeFlow {
  public:
    NodeFlow();
    NodeFlow(ActionTypeIndex typeIndex, ActionStateIndex stateIndex, Database::EntityHandle entityHandle);
    void configure(ActionTypeIndex typeIndex, ActionStateIndex stateIndex, Database::EntityHandle entityHandle);
    void start(NodeIndex nodeIndex);
    bool isCompleted(NodeIndex nodeIndex);
    ActionStateIndex getActionStateIndex() const;
    ActionTypeIndex getActionTypeIndex() const;
    Database::EntityHandle getEntityHandle() const;
  private:
    ActionTypeIndex actionTypeIndex;
    ActionStateIndex actionStateIndex;
    Database::EntityHandle entityHandle;
  };
}

#endif
