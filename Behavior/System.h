#ifndef BEHAVIOR_SYSTEM_H
#define BEHAVIOR_SYSTEM_H

#include "Actions/ComponentHandle.h"
#include "Behavior/Handle.h"
#include "Behavior/BehaviorType.h"

namespace Behavior {
  namespace System {
    void setup();
    Handle create(Actions::ComponentHandle actionsHandle, BehaviorType type);
    void update();
  }
}

#endif
