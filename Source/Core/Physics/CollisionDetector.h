#ifndef PHYSICS_COLLISION_DETECTOR_H
#define PHYSICS_COLLISION_DETECTOR_H

#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/DynamicSphereColliderHandle.h"
#include "Core/Physics/StaticSphereColliderHandle.h"
#include "Core/Physics/FreeList.h"
#include "Quanta/Math/Vector3.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/SphereColliderList.h"

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
    void detect(CollisionSet &set, const Quanta::Vector3 *dynamicPositions, const Quanta::Vector3 *staticPositions);
  private:
    SphereColliderList<DynamicSphereColliderHandle, DynamicBodyIndex> dynamicSphereColliders;
    SphereColliderList<StaticSphereColliderHandle, StaticBodyIndex> staticSphereColliders;
    void detectDynamics(CollisionSet::DynamicList &collisions, const Quanta::Vector3 *positions);
    void detectStatics(CollisionSet::StaticList &collisions, const Quanta::Vector3 *staticPositions, const Quanta::Vector3 *dynamicPositions);
  };
}

#endif
