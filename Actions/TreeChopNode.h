#ifndef ACTIONS_TREE_CHOP_NODE_H
#define ACTIONS_TREE_CHOP_NODE_H

#include <stdint.h>
#include "Actions/NodeFlow.h"

namespace Actions {
  namespace TreeChopNode {
    uint8_t calcConfigLength(const void *args);
    uint8_t calcStateLength(const void *args);
    void configure(const void *args, void *config);
    void start(NodeFlow *flow);
    bool isCompleted(NodeFlow *flow);
  }
}

#endif
