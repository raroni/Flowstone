#include "Core/Physics/Engine.h"
#include "Core/Physics/SphereColliderHandle.h"

namespace Physics {
  const double Engine::stepDuration = 0.03;

  TransformIndex Engine::createTransform() {
    TransformIndex index = transformCount++;
    return index;
  }

  void Engine::createRigidBody(TransformIndex transformIndex) {
    integrator.createRigidBody(transformIndex);
  }

  SphereColliderHandle Engine::createSphereCollider(TransformIndex transformIndex, float radius) {
    return collisionDetector.createSphereCollider(transformIndex, radius);
  }

  void Engine::simulate() {
    integrator.integrate();
    collisionDetector.detect(collisionSet, positions);
    //collisionResolver.resolve();
    collisionSet.clear();
  }

  const Quanta::Vector3* Engine::getPositions() const {
    return positions;
  }

  const Quanta::Quaternion* Engine::getOrientations() const {
    return orientations;
  }
}
