#include "Misc/Error.h"
#include "Physics/CollisionDetector.h"

namespace Physics {
  static Fixie::Num differenceTolerance = 1.0/1024.0;

  void CollisionDetector::detect(CollisionSet &set, const BodyList &bodies) {
    detectDynamics(set.dynamics.values, &set.dynamics.count, bodies);
    detectStatics(set.statics.values, &set.statics.count, bodies);
  }

  void CollisionDetector::detectDynamics(DynamicCollision *collisions, uint16_t *collisionCount, const BodyList &bodies) {
    const Fixie::Vector3 *positions = bodies.positions;
    const Fixie::Num *radii = sphereColliders.radii;
    uint16_t colliderCount = dynamicSphereColliders.count;

    for(uint16_t i=0; i<colliderCount-1; ++i) {
      SphereColliderHandle colliderHandle1 = dynamicSphereColliders.handles[i];
      uint16_t colliderIndex1 = sphereColliders.getIndex(colliderHandle1);
      BodyHandle bodyHandle1 = sphereColliders.bodyHandles[colliderIndex1];
      uint16_t bodyIndex1 = bodies.getIndex(bodyHandle1);
      for(uint16_t n=i+1; n<colliderCount; ++n) {
        SphereColliderHandle colliderHandle2 = dynamicSphereColliders.handles[n];
        uint16_t colliderIndex2 = sphereColliders.getIndex(colliderHandle2);
        BodyHandle bodyHandle2 = sphereColliders.bodyHandles[colliderIndex2];
        uint16_t bodyIndex2 = bodies.getIndex(bodyHandle2);

        Fixie::Vector3 difference = positions[bodyIndex2]-positions[bodyIndex1];
        Fixie::Num differenceSquaredLength = difference.calcSquaredLength();
        Fixie::Num radiiSum = radii[colliderIndex1] + radii[colliderIndex2];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Fixie::Vector3 separation = Fixie::Vector3::zero();
          if(differenceSquaredLength < differenceTolerance) {
            separation[0] = radiiSum;
          } else {
            Fixie::Vector3 direction = Fixie::Vector3::normalize(difference);
            separation = direction*(radiiSum-difference.calcLength());
          }
          collisions->bodyA = bodyHandle1;
          collisions->bodyB = bodyHandle2;
          collisions->separation = separation;
          if(*collisionCount != Config::dynamicCollisionMax) {
            collisions++;
            (*collisionCount)++;
          } else {
            return;
          }
        }
      }
    }
  }

  void CollisionDetector::detectStatics(StaticCollision *collisions, uint16_t *collisionCount, const BodyList &bodies) {
    const Fixie::Vector3 *positions = bodies.positions;
    const Fixie::Num *radii = sphereColliders.radii;
    uint16_t dynamicColliderCount = dynamicSphereColliders.count;
    uint16_t staticColliderCount = staticSphereColliders.count;

    for(uint16_t d=0; d<dynamicColliderCount; ++d) {
      SphereColliderHandle dynamicColliderHandle = dynamicSphereColliders.handles[d];
      uint16_t dynamicColliderIndex = sphereColliders.getIndex(dynamicColliderHandle);
      BodyHandle dynamicBodyHandle = sphereColliders.bodyHandles[dynamicColliderIndex];
      uint16_t dynamicBodyIndex = bodies.getIndex(dynamicBodyHandle);
      for(uint16_t s=0; s<staticColliderCount; ++s) {
        SphereColliderHandle staticColliderHandle = staticSphereColliders.handles[s];
        uint16_t staticColliderIndex = sphereColliders.getIndex(staticColliderHandle);
        BodyHandle staticBodyHandle = sphereColliders.bodyHandles[staticColliderIndex];
        uint16_t staticBodyIndex = bodies.getIndex(staticBodyHandle);

        Fixie::Vector3 difference = positions[dynamicBodyIndex]-positions[staticBodyIndex];
        Fixie::Num differenceSquaredLength = difference.calcSquaredLength();
        Fixie::Num radiiSum = radii[dynamicColliderIndex] + radii[staticColliderIndex];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Fixie::Vector3 separation = Fixie::Vector3::zero();
          if(differenceSquaredLength < differenceTolerance) {
            separation[0] = radiiSum;
          } else {
            Fixie::Vector3 direction = Fixie::Vector3::normalize(difference);
            separation = direction*(radiiSum-difference.calcLength());
          }
          collisions->staticBody = staticBodyHandle;
          collisions->dynamicBody = dynamicBodyHandle;
          collisions->separation = separation;
          if(*collisionCount != Config::staticCollisionMax) {
            collisions++;
            (*collisionCount)++;
          } else {
            return;
          }
        }
      }
    }
  }

  SphereColliderHandle CollisionDetector::createSphereCollider(BodyHandle body, ColliderType type, Fixie::Num radius) {
    SphereColliderHandle handle = sphereColliders.create(body, type, radius);
    switch(type) {
      case ColliderType::Static:
        staticSphereColliders.handles[staticSphereColliders.count++] = handle;
        break;
      case ColliderType::Dynamic:
        dynamicSphereColliders.handles[dynamicSphereColliders.count++] = handle;
        break;
      default:
        fatalError("Unknown sphere collider type.");
        break;
    }
    return handle;
  }

}
