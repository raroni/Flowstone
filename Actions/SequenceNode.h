#ifndef ACTIONS_SEQUENCE_NODE_H
#define ACTIONS_SEQUENCE_NODE_H

#include <stdint.h>
#include "Actions/NodeIndex.h"
#include "Actions/NodeFlow.h"
#include "Actions/ParentNode.h"

namespace Actions {
  namespace SequenceNode {
    typedef ParentNode::CreationArgSet CreationArgSet;
    typedef ParentNode::ConfigArgSet ConfigArgSet;

    uint8_t calcConfigLength(const void *args);
    uint8_t calcStateLength(const void *args);
    void configure(const void *args, void *config);
    void start(NodeFlow *flow);
    bool isCompleted(NodeFlow *flow);
  }
}

#endif
