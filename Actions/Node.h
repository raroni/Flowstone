#ifndef ACTIONS_NODE_H
#define ACTIONS_NODE_H

#include "Actions/NodeInterface.h"
#include "Actions/NodeTypeIndex.h"

namespace Actions {
  namespace Node {
    void setup(NodeTypeIndex index, const NodeInterface *interface);
  }
}

#endif
