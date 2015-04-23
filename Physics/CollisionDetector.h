#ifndef PHYSICS_COLLISION_DETECTOR_H
#define PHYSICS_COLLISION_DETECTOR_H

#include "Fixie/Vector3.h"
#include "Physics/BodyList.h"
#include "Physics/CollisionSet.h"
#include "Physics/SphereColliderList.h"
#include "Physics/SphereSphereCheck.h"

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
    void loadSphereCollider(
      SphereColliderHandle sphereColliderHandle,
      const BodyList &bodies,
      uint16_t *colliderIndex,
      BodyHandle *bodyHandle,
      uint16_t *bodyIndex
    );
    void checkSphereSphere(
      const BodyList &bodies,
      SphereColliderHandle sphereColliderHandle1,
      SphereColliderHandle sphereColliderHandle2,
      SphereSphereCheck &check
    );
    void detectDynamics(DynamicCollisionList &list, const BodyList &bodies);
    void detectStatics(StaticCollisionList &list, const BodyList &bodies);
  };
}

#endif
