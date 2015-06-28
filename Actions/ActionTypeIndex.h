#ifndef ACTIONS_ACTION_TYPE_INDEX_H
#define ACTIONS_ACTION_TYPE_INDEX_H

#include <stdint.h>
#include "Actions/Config.h"

namespace Actions {
  static_assert(Config::actionTypeMax <= UINT8_MAX, "ActionTypeIndex is too small.");
  typedef uint8_t ActionTypeIndex;
}

#endif
