#ifndef WATSON_NODE_INTERFACE_H
#define WATSON_NODE_INTERFACE_H

#include <stdint.h>
#include "Watson/Config.h"
#include "Watson/TraversalFunction.h"
#include "Watson/ResetFlow.h"
#include "Watson/NodeResult.h"
#include "Watson/NodeIndex.h"

namespace Watson {
  struct NodeInterface {
    TraversalFunction react;
    TraversalFunction enter;
    void (*reset)(ResetFlow *flow);
    void (*initializeState)(const void *structure, void *state);
    TraversalFunction callbacks[Config::callbacksPerNodeType];
  };
}

#endif
