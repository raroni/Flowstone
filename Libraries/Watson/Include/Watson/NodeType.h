#ifndef WATSON_NODE_TYPE_H
#define WATSON_NODE_TYPE_H

#include <stdint.h>

namespace Watson {
  enum class NodeType : uint8_t {
    Priority,
    Concurrent,
    Loop,
    Sequence,
    FailDummy,
    RunDummy,

    Count
  };
}

#endif
