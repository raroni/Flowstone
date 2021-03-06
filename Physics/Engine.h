#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Physics/BodyList.h"
#include "Physics/CollisionDetector.h"
#include "Physics/CollisionSet.h"
#include "Physics/Integrator.h"

namespace Physics {
  class Engine {
    public:
      void simulate();
      BodyHandle createBody();
      BodyList& getBodies();
      Body getBody(BodyHandle handle);
      DynamicDriverHandle createDynamicDriver(BodyHandle body);
      DynamicDriver getDynamicDriver(DynamicDriverHandle handle);
      KinematicDriverHandle createKinematicDriver(BodyHandle body);
      SphereColliderHandle createSphereCollider(BodyHandle body, ColliderType type, Fixie::Num radius);
    private:
      BodyList bodies;
      CollisionDetector collisionDetector;
      Integrator integrator;
      CollisionSet collisionSet;
  };
}

#endif
