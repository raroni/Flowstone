#ifndef BEHAVIOR_SYSTEM_H
#define BEHAVIOR_SYSTEM_H

#include "Actions/InstanceHandle.h"
#include "Behavior/Handle.h"
#include "Behavior/BehaviorType.h"

namespace Behavior {
  namespace System {
    void setup();
    Handle create(Actions::InstanceHandle actionsHandle, BehaviorType type);
    void update();
  }
}

#endif
