#ifndef PHYSICS_COLLISION_DETECTOR_H
#define PHYSICS_COLLISION_DETECTOR_H

#include "Fixie/Vector3.h"
#include "Physics/BodyList.h"
#include "Physics/CollisionSet.h"
#include "Physics/SphereColliderList.h"

namespace Physics {
  class CollisionDetector {
  public:
    SphereColliderHandle createSphereCollider(BodyHandle bodyHandle, ColliderType type, Fixie::Num radius);
    void destroySphereCollider(SphereColliderHandle handle);
    void detect(CollisionSet &set, const BodyList &bodies);
  private:
    struct {
      SphereColliderHandle handles[Config::dynamicSphereColliderMax];
      uint16_t count = 0;
    } dynamicSphereColliders;
    struct {
      SphereColliderHandle handles[Config::staticSphereColliderMax];
      uint16_t count = 0;
    } staticSphereColliders;
    SphereColliderList sphereColliders;
    void detectDynamics(DynamicCollision *collisions, uint16_t *collisionsCount, const BodyList &bodies);
    void detectStatics(StaticCollision *collisions, uint16_t *collisionsCount, const BodyList &bodies);
  };
}

#endif
