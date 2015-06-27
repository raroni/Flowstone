#ifndef ACTIONS3_PENDING_REQUESTS_H
#define ACTIONS3_PENDING_REQUESTS_H

#include "Actions3/InstanceHandle.h"
#include "Actions3/Request.h"

namespace Actions3 {
  namespace PendingRequests {
    void set(InstanceHandle handle, const Request *request);
    void process();
  }
}

#endif
