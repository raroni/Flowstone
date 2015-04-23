#include "Misc/Error.h"
#include "Physics/CollisionDetector.h"

namespace Physics {
  static Fixie::Num differenceTolerance = 1.0/1024.0;

  void CollisionDetector::detect(CollisionSet &set, const BodyList &bodies) {
    detectDynamics(set.dynamics.values, &set.dynamics.count, bodies);
    detectStatics(set.statics.values, &set.statics.count, bodies);
  }

  void CollisionDetector::loadSphereCollider(
    SphereColliderHandle sphereColliderHandle,
    const BodyList &bodies,
    uint16_t *colliderIndex,
    BodyHandle *bodyHandle,
    uint16_t *bodyIndex
  ) {
    *colliderIndex = sphereColliders.getIndex(sphereColliderHandle);
    *bodyHandle = sphereColliders.bodyHandles[*colliderIndex];
    *bodyIndex = bodies.getIndex(*bodyHandle);
  }

  void CollisionDetector::checkSphereSphere(
    const BodyList &bodies,
    SphereColliderHandle sphereColliderHandle1,
    SphereColliderHandle sphereColliderHandle2,
    SphereSphereCheck &check
  ) {
    uint16_t colliderIndex1, bodyIndex1, colliderIndex2, bodyIndex2;
    BodyHandle bodyHandle1, bodyHandle2;
    Fixie::Vector3 separation;

    loadSphereCollider(sphereColliderHandle1, bodies, &colliderIndex1, &bodyHandle1, &bodyIndex1);
    loadSphereCollider(sphereColliderHandle2, bodies, &colliderIndex2, &bodyHandle2, &bodyIndex2);

    Fixie::Vector3 difference = bodies.positions[bodyIndex2]-bodies.positions[bodyIndex1];
    Fixie::Num differenceSquaredLength = difference.calcSquaredLength();
    Fixie::Num radiiSum = sphereColliders.radii[colliderIndex1] + sphereColliders.radii[colliderIndex2];
    if(differenceSquaredLength < radiiSum*radiiSum) {
      if(differenceSquaredLength < differenceTolerance) {
        check.separation[0] = radiiSum;
        check.separation[1] = 0;
        check.separation[2] = 0;
      } else {
        Fixie::Vector3 direction = Fixie::Vector3::normalize(difference);
        check.separation = direction*(radiiSum-difference.calcLength());
      }
      check.bodyHandle1 = bodyHandle1;
      check.bodyHandle2 = bodyHandle2;
      check.positive = true;
    } else {
      check.positive = false;
    }
  }

  void CollisionDetector::detectDynamics(DynamicCollision *collisions, uint16_t *collisionCount, const BodyList &bodies) {
    uint16_t colliderCount = dynamicSphereColliders.count;
    SphereSphereCheck sphereSphereCheck;

    for(uint16_t i=0; i<colliderCount-1; ++i) {
      for(uint16_t n=i+1; n<colliderCount; ++n) {
        checkSphereSphere(bodies, dynamicSphereColliders.handles[i], dynamicSphereColliders.handles[n], sphereSphereCheck);
        if(sphereSphereCheck.positive) {
          collisions->bodyA = sphereSphereCheck.bodyHandle1;
          collisions->bodyB = sphereSphereCheck.bodyHandle2;
          collisions->separation = sphereSphereCheck.separation;
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
    uint16_t dynamicColliderCount = dynamicSphereColliders.count;
    uint16_t staticColliderCount = staticSphereColliders.count;
    SphereSphereCheck sphereSphereCheck;

    for(uint16_t d=0; d<dynamicColliderCount; ++d) {
      for(uint16_t s=0; s<staticColliderCount; ++s) {
        checkSphereSphere(bodies, staticSphereColliders.handles[s], dynamicSphereColliders.handles[d], sphereSphereCheck);
        if(sphereSphereCheck.positive) {
          collisions->staticBody = sphereSphereCheck.bodyHandle1;
          collisions->dynamicBody = sphereSphereCheck.bodyHandle2;
          collisions->separation = sphereSphereCheck.separation;
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
