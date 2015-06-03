#ifndef BEHAVIOR_NODE_TYPE_H
#define BEHAVIOR_NODE_TYPE_H

#include <stdint.h>
#include "Watson/NodeType.h"

namespace Behavior {
  enum class NodeType : uint8_t {
    ThreatCheck = static_cast<uint8_t>(Watson::NodeType::Count)
  };
}

#endif
