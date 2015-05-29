#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "AI/Handle.h"
#include "AI/Type.h"

namespace AI {
  namespace System {
    void initialize();
    Handle create(Type type);
    void update();
  }
}

#endif
