#ifndef ACTIONS_NEW_REQUESTS_H
#define ACTIONS_NEW_REQUESTS_H

#include "Actions/Request.h"
#include "Actions/InstanceHandle.h"

namespace Actions {
  namespace NewRequests {
    void set(InstanceHandle handle, const Request *request);
    void process();
  }
}

#endif
