#include "Core/Physics/DynamicSphereColliderHandle.h"
#include "Core/Physics/CollisionResolver.h"
#include "Core/Physics/Engine.h"

namespace Physics {
  DynamicBodyIndex Engine::createDynamicBody() {
    dynamics.orientations[dynamics.count] = Quanta::Quaternion::identity();
    DynamicBodyIndex index = dynamics.count++;
    integrator.activate(index);
    return index;
  }

  DynamicSphereColliderHandle Engine::createDynamicSphereCollider(DynamicBodyIndex body, float radius) {
    return collisionDetector.createDynamicSphere(body, radius);
  }

  void Engine::simulate() {
    integrator.integrate(dynamics.positions, dynamics.velocities, dynamics.forces);
    collisionDetector.detect(collisionSet, dynamics.positions);
    resolveCollisions(collisionSet, dynamics.positions, dynamics.velocities);
    collisionSet.clear();
  }

  const Quanta::Vector3* Engine::getDynamicPositions() const {
    return dynamics.positions;
  }

  Quanta::Vector3* Engine::getDynamicForces() {
    return dynamics.forces;
  }

  const Quanta::Vector3* Engine::getDynamicVelocities() const {
    return dynamics.velocities;
  }

  const Quanta::Quaternion* Engine::getDynamicOrientations() const {
    return dynamics.orientations;
  }

  DynamicBody Engine::getDynamicBody(DynamicBodyIndex index) {
    DynamicBody body;
    body.position = &dynamics.positions[index];
    body.velocity = &dynamics.velocities[index];
    body.force = &dynamics.forces[index];
    body.orientation = &dynamics.orientations[index];
    return body;
  }
}
