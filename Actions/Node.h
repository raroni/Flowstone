#ifndef ACTIONS_NODE_H
#define ACTIONS_NODE_H

#include "Actions/NodeFlow.h"
#include "Actions/NodeInterface.h"
#include "Actions/NodeTypeIndex.h"

namespace Actions {
  namespace Node {
    void setup(NodeTypeIndex index, const NodeInterface *interface);
    uint8_t calcConfigLength(NodeTypeIndex index, const void *args);
    uint8_t calcStateLength(NodeTypeIndex index, const void *args);
    void configure(NodeTypeIndex index, const void *args, void *config);
    void start(NodeTypeIndex index, NodeFlow *flow);
  }
}

#endif
