#include "Fixie/TransformFactory.h"
#include "Physics/DynamicSphereColliderHandle.h"
#include "Physics/CollisionResolver.h"
#include "Physics/Engine.h"

namespace Physics {
  DynamicBodyIndex Engine::createDynamicBody() {
    dynamics.orientations[dynamics.count] = Fixie::Quaternion::identity();
    DynamicBodyIndex index = dynamics.count++;
    integrator.activate(index);
    return index;
  }

  StaticBodyIndex Engine::createStaticBody() {
    statics.orientations[statics.count] = Fixie::Quaternion::identity();
    statics.transforms[statics.count] = Fixie::Matrix4::identity();
    StaticBodyIndex index = statics.count++;
    return index;
  }

  DynamicSphereColliderHandle Engine::createDynamicSphereCollider(DynamicBodyIndex body, float radius) {
    return collisionDetector.createDynamicSphere(body, radius);
  }

  StaticSphereColliderHandle Engine::createStaticSphereCollider(StaticBodyIndex body, float radius) {
    return collisionDetector.createStaticSphere(body, radius);
  }

  void Engine::simulate() {
    updateStaticTransforms();
    integrator.integrate(dynamics.positions, dynamics.velocities, dynamics.forces);
    collisionDetector.detect(collisionSet, dynamics.positions, statics.positions);
    resolveCollisions(collisionSet, dynamics.positions, dynamics.velocities);
    collisionSet.clear();
  }

  void Engine::updateStaticTransforms() {
    Fixie::Matrix4 transform;
    for(uint16_t i=0; statics.count>i; i++) {
      statics.transforms[i] = Fixie::TransformFactory::translation(statics.positions[i]);
      // todo rotation
    }
  }

  const Fixie::Vector3* Engine::getDynamicPositions() const {
    return dynamics.positions;
  }

  Fixie::Vector3* Engine::getDynamicForces() {
    return dynamics.forces;
  }

  const Fixie::Vector3* Engine::getDynamicVelocities() const {
    return dynamics.velocities;
  }

  const Fixie::Quaternion* Engine::getDynamicOrientations() const {
    return dynamics.orientations;
  }

  const Fixie::Matrix4* Engine::getStaticTransforms() const {
    return statics.transforms;
  }

  DynamicBody Engine::getDynamicBody(DynamicBodyIndex index) {
    DynamicBody body;
    body.position = &dynamics.positions[index];
    body.velocity = &dynamics.velocities[index];
    body.force = &dynamics.forces[index];
    body.orientation = &dynamics.orientations[index];
    return body;
  }

  StaticBody Engine::getStaticBody(StaticBodyIndex index) {
    StaticBody body;
    body.position = &statics.positions[index];
    body.orientation = &statics.orientations[index];
    return body;
  }
}
