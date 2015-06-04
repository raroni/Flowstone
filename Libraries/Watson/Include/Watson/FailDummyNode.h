#ifndef WATSON_FAIL_DUMMY_NODE_H
#define WATSON_FAIL_DUMMY_NODE_H

#include "Watson/NodeResult.h"
#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace Watson {
  namespace FailDummyNode {
    void enter(TraversalFlow *flow);
    void reset(ResetFlow *flow);
    void initializeState(const void *structure, void *state);
    extern uint8_t structureLength;
    extern uint8_t stateLength;
  }
}

#endif
