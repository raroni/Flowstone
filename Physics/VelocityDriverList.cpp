#include "Physics/VelocityDriverList.h"

namespace Physics {
  VelocityDriverHandle VelocityDriverList::create(BodyHandle bodyHandle) {
    bodyHandles[count] = bodyHandle;
    return count++;
  }
}
