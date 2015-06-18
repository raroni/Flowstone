#ifndef ACTIONS_NODE_CALL_H
#define ACTIONS_NODE_CALL_H

#include "Actions/NodeFlow.h"

namespace Actions {
  class NodeCall {
  public:
    NodeCall(NodeFlow *flow, NodeIndex index);
    NodeFlow* getFlow();
    const void* getConfig() const;
    void* getState();
    NodeTypeIndex getNodeType() const;
  private:
    NodeFlow *flow = nullptr;
    const void *structure;
    void *state;

  };
}

#endif
