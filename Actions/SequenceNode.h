#ifndef ACTIONS_SEQUENCE_NODE_H
#define ACTIONS_SEQUENCE_NODE_H

#include <stdint.h>

namespace Actions {
  namespace SequenceNode {
    uint8_t calcConfigLength(uint8_t childCount);
    extern uint8_t stateLength;
    void writeConfig(void *config, uint8_t childCount);
    void start(const void *config, void *state);
  }
}

#endif
