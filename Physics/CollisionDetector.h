#ifndef PHYSICS_COLLISION_DETECTOR_H
#define PHYSICS_COLLISION_DETECTOR_H

#include "Physics/DynamicBodyIndex.h"
#include "Physics/DynamicSphereColliderHandle.h"
#include "Physics/StaticSphereColliderHandle.h"
#include "Physics/FreeList.h"
#include "Fixie/Vector3.h"
#include "Physics/CollisionSet.h"
#include "Physics/SphereColliderList.h"

namespace Physics {
  class CollisionDetector {
  public:
    DynamicSphereColliderHandle createDynamicSphere(DynamicBodyIndex body, float radius) {
      return dynamicSphereColliders.create(body, radius);
    }
    StaticSphereColliderHandle createStaticSphere(StaticBodyIndex body, float radius) {
      return staticSphereColliders.create(body, radius);
    }
    void destroyDynamicSphere(DynamicSphereColliderHandle handle) {
      dynamicSphereColliders.destroy(handle);
    }
    void detect(CollisionSet &set, const Fixie::Vector3 *dynamicPositions, const Fixie::Vector3 *staticPositions);
  private:
    SphereColliderList<DynamicSphereColliderHandle, DynamicBodyIndex> dynamicSphereColliders;
    SphereColliderList<StaticSphereColliderHandle, StaticBodyIndex> staticSphereColliders;
    void detectDynamics(CollisionSet::DynamicList &collisions, const Fixie::Vector3 *positions);
    void detectStatics(CollisionSet::StaticList &collisions, const Fixie::Vector3 *staticPositions, const Fixie::Vector3 *dynamicPositions);
  };
}

#endif
