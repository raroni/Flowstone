#ifndef ACTIONS_STATUS_H
#define ACTIONS_STATUS_H

#include <stdint.h>

namespace Actions {
  enum class Status : uint8_t {
    Initialized,
    Running,
    Failed,
    Cancelled,
    Completed
  };
}

#endif
