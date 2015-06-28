#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include "Database/EntityHandle.h"
#include "Actions/InstanceHandle.h"
#include "Actions/Request.h"
#include "Actions/InstanceStatus.h"

namespace Actions {
  namespace System {
    void setup();
    InstanceHandle createInstance(Database::EntityHandle entity);
    void update();
    const Request* getPendingRequest(InstanceHandle handle);
    InstanceStatus getStatus(InstanceHandle handle);
    void request(InstanceHandle handle, const Request *request);
  }
}

#endif
