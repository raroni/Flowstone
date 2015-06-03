#ifndef WATSON_NODE_H
#define WATSON_NODE_H

#include <stdint.h>
#include "Watson/NodeInterface.h"
#include "Watson/NodeResult.h"

namespace Watson {
  namespace Node {
    void setupInterface(uint8_t type, NodeInterface interface);
    void enter(TraversalFlow *flow);
    void react(TraversalFlow *flow);
    void reset(ResetFlow *flow);
    void initializeState(const void *structure, void *state);
    uint16_t getStateLength();
  }
}

#endif
