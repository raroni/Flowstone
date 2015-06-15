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
    const void* getConfig() const;
    void* getState();
    NodeTypeIndex getNodeType() const;
    Database::EntityHandle getEntityHandle() const;
  private:
    void prepare(NodeIndex nodeIndex);
    const void *structure;
    void *state;
    ActionTypeIndex actionTypeIndex;
    ActionStateIndex actionStateIndex;
    Database::EntityHandle entityHandle;
  };
}

#endif
