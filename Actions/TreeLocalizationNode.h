#ifndef ACTIONS_TREE_LOCALIZATION_NODE_H
#define ACTIONS_TREE_LOCALIZATION_NODE_H

#include <stdint.h>

namespace Actions {
  namespace TreeLocalizationNode {
    extern uint8_t configLength;
    extern uint8_t stateLength;

    void start(const void *config, void *state);
  }
}

#endif
