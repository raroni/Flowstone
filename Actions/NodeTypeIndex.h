#ifndef ACTIONS_NODE_TYPE_INDEX_H
#define ACTIONS_NODE_TYPE_INDEX_H

#include <stdint.h>

namespace Actions {
  enum class NodeTypeIndex : uint8_t {
    Sequence,
    TreeLocalization,

    Count
  };
}

#endif
