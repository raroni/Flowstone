#include "Physics/SphereColliderList.h"

namespace Physics {
  SphereColliderHandle SphereColliderList::create(BodyHandle bodyHandle, ColliderType type, Fixie::Num radius) {
    bodyHandles[count] = bodyHandle;
    types[count] = type;
    radii[count] = radius;
    return count++;
  }

  uint16_t SphereColliderList::getIndex(SphereColliderHandle handle) {
    return handle;
  }

  uint16_t SphereColliderList::getCount() const {
    return count;
  }
}
