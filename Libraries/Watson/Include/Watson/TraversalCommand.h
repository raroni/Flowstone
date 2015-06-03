#ifndef WATSON_TRAVERSAL_COMMAND_H
#define WATSON_TRAVERSAL_COMMAND_H

#include "Watson/NodeIndex.h"
#include "Watson/TraversalCommandType.h"
#include "Watson/NodeResult.h"

namespace Watson {
  struct TraversalCommand {
    TraversalCommandType type = TraversalCommandType::Undefined;
    union {
      NodeIndex targetNodeIndex;
      NodeResult result;
      uint8_t callbackIndex;
    } options;
  };
}

#endif
