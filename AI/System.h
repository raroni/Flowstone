#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "AI/Handle.h"
#include "AI/BehaviorType.h"

namespace AI {
  namespace System {
    void setup();
    Handle create(BehaviorType type);
    void update();
  }
}

#endif
