#ifndef ACTIONS_NODE_INTERFACE_H
#define ACTIONS_NODE_INTERFACE_H

#include "Actions/NodeFlow.h"

namespace Actions {
  struct NodeInterface {
    typedef void (*StartFunction)(NodeFlow *flow);
    typedef bool (*IsCompletedFunction)(NodeFlow *flow);
    typedef uint8_t (*CalcLengthFunction)(const void *args);
    typedef void (*ConfigureFunction)(const void *args, void *config);

    StartFunction start;
    IsCompletedFunction isCompleted;
    CalcLengthFunction calcConfigLength;
    CalcLengthFunction calcStateLength;
    ConfigureFunction configure;
  };
}

#endif
