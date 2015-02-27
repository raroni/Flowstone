#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Common/Physics/CollisionDetector.h"
#include "Common/Physics/DynamicBodyIndex.h"
#include "Common/Physics/CollisionSet.h"
#include "Common/Physics/Integrator.h"
#include "Common/Physics/Config.h"
#include "Common/Physics/DynamicBody.h"
#include "Common/Physics/StaticBody.h"

namespace Physics {
  class Engine {
    public:
      DynamicBodyIndex createDynamicBody();
      DynamicSphereColliderHandle createDynamicSphereCollider(DynamicBodyIndex body, float radius);
      StaticSphereColliderHandle createStaticSphereCollider(StaticBodyIndex body, float radius);
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
