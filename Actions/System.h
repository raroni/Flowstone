#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include "Actions/Handle.h"
#include "Actions/Request.h"

namespace Actions {
  namespace System {
    Handle create();
    void update();
    void request(Handle handle, const Request *request);
  }
}

#endif
