#include "Physics/KinematicDriverList.h"

namespace Physics {
  KinematicDriverHandle KinematicDriverList::create(BodyHandle bodyHandle) {
    bodyHandles[count] = bodyHandle;
    return count++;
  }
}
