#ifndef ACTIONS3_NEW_REQUESTS_H
#define ACTIONS3_NEW_REQUESTS_H

#include "Actions3/ActionType.h"
#include "Actions3/InstanceHandle.h"

namespace Actions3 {
  namespace NewRequests {
    void set(InstanceHandle handle, ActionType actionType);
    void process();
  }
}

#endif
