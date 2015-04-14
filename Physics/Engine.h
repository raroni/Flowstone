#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <stdint.h>
#include "Fixie/Vector3.h"
#include "Fixie/Matrix4.h"
#include "Fixie/Quaternion.h"
#include "Physics/CollisionDetector.h"
#include "Physics/DynamicBodyIndex.h"
#include "Physics/CollisionSet.h"
#include "Physics/Integrator.h"
#include "Physics/Config.h"
#include "Physics/DynamicBody.h"
#include "Physics/StaticBody.h"

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
      const Fixie::Vector3* getDynamicPositions() const;
      Fixie::Vector3* getDynamicForces();
      const Fixie::Vector3* getDynamicVelocities() const;
      const Fixie::Quaternion* getDynamicOrientations() const;
      const Fixie::Matrix4* getStaticTransforms() const;
    private:
      struct {
        Fixie::Vector3 positions[Config::maxDynamicBodies];
        Fixie::Quaternion orientations[Config::maxDynamicBodies];
        Fixie::Vector3 velocities[Config::maxDynamicBodies];
        Fixie::Vector3 forces[Config::maxDynamicBodies];
        uint16_t count = 0;
      } dynamics;
      struct {
        Fixie::Vector3 positions[Config::maxStaticBodies];
        Fixie::Quaternion orientations[Config::maxStaticBodies];
        Fixie::Matrix4 transforms[Config::maxStaticBodies];
        uint16_t count = 0;
      } statics;
      CollisionDetector collisionDetector;
      Integrator integrator;
      CollisionSet collisionSet;
      void updateStaticTransforms();
  };
}

#endif
