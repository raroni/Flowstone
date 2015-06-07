#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include "Actions/ComponentHandle.h"
#include "Actions/Request.h"
#include "Actions/Status.h"

namespace Actions {
  namespace System {
    void setup();
    ComponentHandle createComponent();
    const Request* getActiveRequest(ComponentHandle handle);
    Status getStatus(ComponentHandle handle);
    void update();
    void request(ComponentHandle handle, const Request *request);
  }
}

#endif
