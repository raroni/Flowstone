#ifndef ACTIONS_NODE_INTERFACE_H
#define ACTIONS_NODE_INTERFACE_H

#include "Actions/NodeCall.h"

namespace Actions {
  struct NodeInterface {
    typedef void (*StartFunction)(NodeCall *call);
    typedef bool (*IsCompletedFunction)(NodeCall *call);
    typedef uint8_t (*CalcLengthFunction)(const void *args);
    typedef void (*ConfigureFunction)(const void *args, void *config);

    StartFunction start = nullptr;
    IsCompletedFunction isCompleted = nullptr;
    CalcLengthFunction calcConfigLength = nullptr;
    CalcLengthFunction calcStateLength = nullptr;
    ConfigureFunction configure = nullptr;
  };
}

#endif
