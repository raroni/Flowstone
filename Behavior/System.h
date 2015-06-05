#ifndef BEHAVIOR_SYSTEM_H
#define BEHAVIOR_SYSTEM_H

#include "Actions/Handle.h"
#include "Behavior/Handle.h"
#include "Behavior/BehaviorType.h"

namespace Behavior {
  namespace System {
    void setup();
    Handle create(Actions::Handle actionsHandle, BehaviorType type);
    void update();
  }
}

#endif
