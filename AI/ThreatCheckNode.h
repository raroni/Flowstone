#ifndef AI_THREAT_CHECK_NODE_H
#define AI_THREAT_CHECK_NODE_H

#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace AI {
  namespace ThreatCheckNode {
    extern const uint8_t structureLength;
    extern const uint8_t stateLength;

    void enter(Watson::TraversalFlow *flow);
    void reset(Watson::ResetFlow *flow);
    void initializeState(const void *structure, void *state);
  }
}

#endif
