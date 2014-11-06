#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Core/Physics/CollisionDetector.h"
#include "Core/Physics/TransformIndex.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/Integrator.h"

namespace Physics {
  class Engine {
    Quanta::Vector3 positions[128];
    Quanta::Quaternion orientations[128];
    uint16_t transformCount = 0;
    CollisionDetector collisionDetector;
    Integrator integrator;
    CollisionSet collisionSet;
    public:
      static const double stepDuration;
      TransformIndex createTransform();
      void createRigidBody(TransformIndex transformIndex);
      SphereColliderHandle createSphereCollider(TransformIndex transformIndex, float radius);
      void simulate();
      const Quanta::Vector3* getPositions() const;
      const Quanta::Quaternion* getOrientations() const;
  };
}

#endif
