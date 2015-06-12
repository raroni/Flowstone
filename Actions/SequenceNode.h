#ifndef ACTIONS_SEQUENCE_NODE_H
#define ACTIONS_SEQUENCE_NODE_H

#include <stdint.h>
#include "Actions/NodeIndex.h"
#include "Actions/NodeFlow.h"

namespace Actions {
  namespace SequenceNode {
    struct CreationArgSet {
      uint8_t childCount;
    };

    struct ConfigArgSet {
      uint8_t childCount;
      NodeIndex *children;
    };

    uint8_t calcConfigLength(const void *args);
    uint8_t calcStateLength(const void *args);
    void configure(const void *args, void *config);
    void start(NodeFlow *flow);
  }
}

#endif
