#ifndef ACTIONS_PENDING_REQUESTS_H
#define ACTIONS_PENDING_REQUESTS_H

#include "Actions/InstanceHandle.h"
#include "Actions/Request.h"

namespace Actions {
  namespace PendingRequests {
    void set(InstanceHandle handle);
    void process();
  }
}

#endif
