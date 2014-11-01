#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"

namespace Physics {
  class Engine {
    Quanta::Vector3 positions[128];
    Quanta::Quaternion orientations[128];
    public:
      static const double stepDuration;
      uint8_t createTransform();
      void createRigidBody(uint8_t transformID);
      void createSphereCollider(uint8_t transformID);
      void simulate();
      const Quanta::Vector3* getPositions() const;
      const Quanta::Quaternion* getOrientations() const;
  };
}

#endif
