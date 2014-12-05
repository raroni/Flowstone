#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Core/Physics/CollisionDetector.h"
#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/Integrator.h"
#include "Core/Physics/Config.h"
#include "Core/Physics/DynamicBody.h"
#include "Core/Physics/StaticBody.h"

namespace Physics {
  class Engine {
    public:
      DynamicBodyIndex createDynamicBody();
      DynamicSphereColliderHandle createDynamicSphereCollider(DynamicBodyIndex body, float radius);
      DynamicBody getDynamicBody(DynamicBodyIndex index);
      StaticBody getStaticBody(StaticBodyIndex index);
      StaticBodyIndex createStaticBody();
      void simulate();
      const Quanta::Vector3* getDynamicPositions() const;
      Quanta::Vector3* getDynamicForces();
      const Quanta::Vector3* getDynamicVelocities() const;
      const Quanta::Quaternion* getDynamicOrientations() const;
      const Quanta::Matrix4* getStaticTransforms() const;
    private:
      struct {
        Quanta::Vector3 positions[Config::maxDynamicBodies];
        Quanta::Quaternion orientations[Config::maxDynamicBodies];
        Quanta::Vector3 velocities[Config::maxDynamicBodies];
        Quanta::Vector3 forces[Config::maxDynamicBodies];
        uint16_t count = 0;
      } dynamics;
      struct {
        Quanta::Vector3 positions[Config::maxStaticBodies];
        Quanta::Quaternion orientations[Config::maxStaticBodies];
        Quanta::Matrix4 transforms[Config::maxStaticBodies];
        uint16_t count = 0;
      } statics;
      CollisionDetector collisionDetector;
      Integrator integrator;
      CollisionSet collisionSet;
      void updateStaticTransforms();
  };
}

#endif
