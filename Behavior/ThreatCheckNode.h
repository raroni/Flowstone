#ifndef BEHAVIOR_THREAT_CHECK_NODE_H
#define BEHAVIOR_THREAT_CHECK_NODE_H

#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace Behavior {
  namespace ThreatCheckNode {
    extern const uint8_t structureLength;
    extern const uint8_t stateLength;

    enum CallbackIndex {
      ResponseCallbackIndex
    };

    void enter(Watson::TraversalFlow *flow);
    void handleResponse(Watson::TraversalFlow *flow);
    void reset(Watson::ResetFlow *flow);
    void initializeState(const void *structure, void *state);
  }
}

#endif
