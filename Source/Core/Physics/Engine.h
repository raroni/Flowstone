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
    Quanta::Vector3 dynamicPositions[Config::maxDynamicBodies];
    Quanta::Quaternion dynamicOrientations[Config::maxDynamicBodies] = { Quanta::Quaternion::identity() };
    Quanta::Vector3 dynamicVelocities[Config::maxDynamicBodies];
    Quanta::Vector3 dynamicForces[Config::maxDynamicBodies];
    uint16_t dynamicBodyCount = 0;
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
