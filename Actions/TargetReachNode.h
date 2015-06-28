#ifndef ACTIONS_TARGET_REACH_NODE_H
#define ACTIONS_TARGET_REACH_NODE_H

#include <stdint.h>
#include "Actions/NodeCall.h"

namespace Actions {
  namespace TargetReachNode {
    uint8_t calcConfigLength(const void *args);
    uint8_t calcStateLength(const void *args);
    void configure(const void *args, void *config);
    void start(NodeCall *call);
    bool isCompleted(NodeCall *call);
  }
}

#endif
