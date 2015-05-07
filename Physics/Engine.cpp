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

  DynamicDriver Engine::getDynamicDriver(DynamicDriverHandle handle) {
    return integrator.getDynamicDriver(handle);
  }

  DynamicDriverHandle Engine::createDynamicDriver(BodyHandle body) {
    return integrator.createDynamicDriver(body);
  }

  KinematicDriverHandle Engine::createKinematicDriver(BodyHandle body) {
    return integrator.createKinematicDriver(body);
  }

  SphereColliderHandle Engine::createSphereCollider(BodyHandle body, ColliderType type, Fixie::Num radius) {
    return collisionDetector.createSphereCollider(body, type, radius);
  }
}
