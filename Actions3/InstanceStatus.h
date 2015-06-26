#ifndef ACTIONS3_INSTANCE_STATUS_H
#define ACTIONS3_INSTANCE_STATUS_H

#include <stdint.h>

namespace Actions3 {
  enum class InstanceStatus : uint8_t {
    Initialized,
    Executing,
    Cancelling,
    Cancelled,
    Completed
  };
}

#endif
