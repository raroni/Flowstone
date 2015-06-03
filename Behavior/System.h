#ifndef BEHAVIOR_SYSTEM_H
#define BEHAVIOR_SYSTEM_H

#include "Behavior/Handle.h"
#include "Behavior/BehaviorType.h"

namespace Behavior {
  namespace System {
    void setup();
    Handle create(BehaviorType type);
    void update();
  }
}

#endif
