#ifndef ACTIONS3_ACTION_TYPE_H
#define ACTIONS3_ACTION_TYPE_H

#include <stdint.h>

namespace Actions3 {
  enum class ActionType : uint8_t {
    None,
    WoodAcquisition,

    Count
  };
}

#endif
