#ifndef AI_NODE_TYPE_H
#define AI_NODE_TYPE_H

#include <stdint.h>
#include "Watson/NodeType.h"

namespace AI {
  enum class NodeType : uint8_t {
    ThreatCheck = static_cast<uint8_t>(Watson::NodeType::Count)
  };
}

#endif
