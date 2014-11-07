#include "Core/Physics/Engine.h"
#include "Core/Physics/DynamicSphereColliderHandle.h"

namespace Physics {
  const double Engine::stepDuration = 0.03;

  DynamicBodyIndex Engine::createDynamicBody() {
    DynamicBodyIndex index = dynamicBodyCount++;
    return index;
  }

  DynamicSphereColliderHandle Engine::createDynamicSphereCollider(DynamicBodyIndex body, float radius) {
    return collisionDetector.createDynamicSphere(body, radius);
  }

  void Engine::simulate() {
    integrator.integrate();
    collisionDetector.detect(collisionSet, dynamicPositions);
    //collisionResolver.resolve();
    collisionSet.clear();
  }

  const Quanta::Vector3* Engine::getDynamicPositions() const {
    return dynamicPositions;
  }

  const Quanta::Quaternion* Engine::getDynamicOrientations() const {
    return dynamicOrientations;
  }
}
