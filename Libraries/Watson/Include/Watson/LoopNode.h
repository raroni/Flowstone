#ifndef WATSON_LOOP_NODE_H
#define WATSON_LOOP_NODE_H

#include "Watson/NodeResult.h"
#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace Watson {
  namespace LoopNode {
    void enter(TraversalFlow *flow);
    void react(TraversalFlow *flow);
    void reset(ResetFlow *flow);
    void setChild(void *structure, NodeIndex childIndex);
    void initializeState(const void *structure, void *state);
    extern uint8_t structureLength;
    extern uint8_t stateLength;
  }
}

#endif
