#ifndef WATSON_INVERTER_NODE_H
#define WATSON_INVERTER_NODE_H

#include "Watson/NodeResult.h"
#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace Watson {
  namespace InverterNode {
    void enter(TraversalFlow *flow);
    void react(TraversalFlow *flow);
    void reset(ResetFlow *flow);
    void initializeState(const void *structure, void *state);
    void setChild(void *structure, NodeIndex childIndex);
    extern uint8_t structureLength;
    extern uint8_t stateLength;
  }
}

#endif
