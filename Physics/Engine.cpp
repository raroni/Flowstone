#include "Fixie/TransformFactory.h"
#include "Physics/CollisionResolver.h"
#include "Physics/Engine.h"

namespace Physics {
  void Engine::simulate() {
    integrator.integrate(bodies);
    collisionDetector.detect(collisionSet, bodies);
    resolveCollisions(collisionSet, bodies);
    collisionSet.clear();
  }

  BodyList& Engine::getBodies() {
    return bodies;
  }

  BodyHandle Engine::createBody() {
    return bodies.create();
  }

  Body Engine::getBody(BodyHandle handle) {
    return bodies.get(handle);
  }

  ForceDriver Engine::getForceDriver(ForceDriverHandle handle) {
    return integrator.getForceDriver(handle);
  }

  ForceDriverHandle Engine::createForceDriver(BodyHandle body) {
    return integrator.createForceDriver(body);
  }

  VelocityDriverHandle Engine::createVelocityDriver(BodyHandle body) {
    return integrator.createVelocityDriver(body);
  }

  SphereColliderHandle Engine::createSphereCollider(BodyHandle body, ColliderType type, Fixie::Num radius) {
    return collisionDetector.createSphereCollider(body, type, radius);
  }
}
