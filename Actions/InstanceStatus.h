#ifndef ACTIONS_INSTANCE_STATUS_H
#define ACTIONS_INSTANCE_STATUS_H

#include <stdint.h>

namespace Actions {
  enum class InstanceStatus : uint8_t {
    Initialized,
    Executing,
    Cancelling,
    Cancelled,
    Completed
  };
}

#endif
