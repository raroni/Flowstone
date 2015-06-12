#ifndef ACTIONS_TREE_LOCALIZATION_NODE_H
#define ACTIONS_TREE_LOCALIZATION_NODE_H

#include <stdint.h>

namespace Actions {
  namespace TreeLocalizationNode {
    uint8_t calcConfigLength(const void *args);
    uint8_t calcStateLength(const void *args);
    void start(const void *config, void *state);
  }
}

#endif
