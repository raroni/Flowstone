#ifndef ACTIONS_PARENT_NODE_H
#define ACTIONS_PARENT_NODE_H

#include <stdint.h>
#include "Actions/NodeIndex.h"

namespace Actions {
  namespace ParentNode {
    struct CreationArgSet {
      uint8_t childCount;
    };

    struct ConfigArgSet {
      uint8_t childCount;
      NodeIndex *children;
    };

    uint8_t calcConfigLength(const void *args);
    const NodeIndex* getChildren(const void *config);
    NodeIndex* getChildren(void *mutableConfig);
    void configure(const void *args, void *config);
    uint8_t getChildCount(const void *config);
  }
}

#endif
