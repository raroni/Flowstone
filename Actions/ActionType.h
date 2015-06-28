#ifndef ACTIONS_ACTION_TYPE_H
#define ACTIONS_ACTION_TYPE_H

#include <stdint.h>

namespace Actions {
  enum class ActionType : uint8_t {
    None,
    WoodAcquisition,

    Count
  };
}

#endif
