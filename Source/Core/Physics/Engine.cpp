#include "Core/Physics/DynamicSphereColliderHandle.h"
#include "Core/Physics/CollisionResolver.h"
#include "Core/Physics/Engine.h"

namespace Physics {
  DynamicBodyIndex Engine::createDynamicBody() {
    dynamicOrientations[dynamicBodyCount] = Quanta::Quaternion::identity();
    DynamicBodyIndex index = dynamicBodyCount++;
    integrator.activate(index);
    return index;
  }

  DynamicSphereColliderHandle Engine::createDynamicSphereCollider(DynamicBodyIndex body, float radius) {
    return collisionDetector.createDynamicSphere(body, radius);
  }

  void Engine::simulate() {
    integrator.integrate(dynamicPositions, dynamicVelocities, dynamicForces);
    collisionDetector.detect(collisionSet, dynamicPositions);
    resolveCollisions(collisionSet, dynamicPositions, dynamicVelocities);
    collisionSet.clear();
  }

  const Quanta::Vector3* Engine::getDynamicPositions() const {
    return dynamicPositions;
  }

  Quanta::Vector3* Engine::getDynamicForces() {
    return dynamicForces;
  }

  const Quanta::Vector3* Engine::getDynamicVelocities() const {
    return dynamicVelocities;
  }

  const Quanta::Quaternion* Engine::getDynamicOrientations() const {
    return dynamicOrientations;
  }

  DynamicBody Engine::getDynamicBody(DynamicBodyIndex index) {
    DynamicBody body;
    body.position = &dynamicPositions[index];
    body.velocity = &dynamicVelocities[index];
    body.force = &dynamicForces[index];
    body.orientation = &dynamicOrientations[index];
    return body;
  }
}
