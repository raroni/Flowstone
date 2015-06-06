#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include "Actions/Handle.h"
#include "Actions/Request.h"
#include "Actions/Status.h"

namespace Actions {
  namespace System {
    void setup();
    Handle create();
    Request getRequest(Handle handle);
    Status getStatus(Handle handle);
    void update();
    void request(Handle handle, const Request *request);
  }
}

#endif
