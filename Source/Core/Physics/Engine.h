#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Core/Physics/CollisionDetector.h"
#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/Integrator.h"
#include "Core/Physics/Config.h"
#include "Core/Physics/DynamicBody.h"

namespace Physics {
  class Engine {
    struct {
      Quanta::Vector3 positions[Config::maxDynamicBodies];
      Quanta::Quaternion orientations[Config::maxDynamicBodies];
      Quanta::Vector3 velocities[Config::maxDynamicBodies];
      Quanta::Vector3 forces[Config::maxDynamicBodies];
      uint16_t count = 0;
    } dynamics;
    CollisionDetector collisionDetector;
    Integrator integrator;
    CollisionSet collisionSet;
    public:
      DynamicBodyIndex createDynamicBody();
      DynamicSphereColliderHandle createDynamicSphereCollider(DynamicBodyIndex body, float radius);
      DynamicBody getDynamicBody(DynamicBodyIndex index);
      void simulate();
      const Quanta::Vector3* getDynamicPositions() const;
      Quanta::Vector3* getDynamicForces();
      const Quanta::Vector3* getDynamicVelocities() const;
      const Quanta::Quaternion* getDynamicOrientations() const;
  };
}

#endif
