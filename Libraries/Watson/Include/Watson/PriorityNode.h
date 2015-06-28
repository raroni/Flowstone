#ifndef WATSON_PRIORITY_NODE_H
#define WATSON_PRIORITY_NODE_H

#include "Watson/NodeResult.h"
#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"

namespace Watson {
  namespace PriorityNode {
    void enter(TraversalFlow *flow);
    void react(TraversalFlow *flow);
    void reset(ResetFlow *flow);
    void initializeState(const void *structure, void *state);
    void writeStructure(void *structure, uint8_t childCount);
    void setChild(void *structure, uint8_t childSlot, NodeIndex childIndex);
    uint8_t calcStructureLength(uint8_t childCount);
    uint8_t calcStateLength(uint8_t childCount);
  }
}

#endif
