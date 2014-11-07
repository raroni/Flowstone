#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Core/Physics/CollisionDetector.h"
#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/Integrator.h"

namespace Physics {
  class Engine {
    Quanta::Vector3 dynamicPositions[128];
    Quanta::Quaternion dynamicOrientations[128];
    uint16_t dynamicBodyCount = 0;
    CollisionDetector collisionDetector;
    Integrator integrator;
    CollisionSet collisionSet;
    public:
      static const double stepDuration;
      DynamicBodyIndex createDynamicBody();
      DynamicSphereColliderHandle createDynamicSphereCollider(DynamicBodyIndex body, float radius);
      void simulate();
      const Quanta::Vector3* getDynamicPositions() const;
      const Quanta::Quaternion* getDynamicOrientations() const;
  };
}

#endif
