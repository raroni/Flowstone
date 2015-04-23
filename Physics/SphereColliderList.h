#ifndef PHYSICS_SPHERE_COLLIDER_H
#define PHYSICS_SPHERE_COLLIDER_H

#include "Physics/BodyHandle.h"
#include "Physics/SphereColliderHandle.h"
#include "Physics/ColliderType.h"
#include "Physics/Config.h"
#include "Fixie/Num.h"

namespace Physics {
  class SphereColliderList {
  public:
    SphereColliderHandle create(BodyHandle bodyHandle, ColliderType type, Fixie::Num radius);
    uint16_t getCount() const;
    uint16_t getIndex(SphereColliderHandle handle);
    Fixie::Num radii[Config::sphereColliderMax];
    ColliderType types[Config::sphereColliderMax];
    BodyHandle bodyHandles[Config::sphereColliderMax];
  private:
    uint16_t count = 0;
  };
}

#endif
