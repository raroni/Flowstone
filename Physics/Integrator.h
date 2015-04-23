#ifndef PHYSICS_INTEGRATOR_H
#define PHYSICS_INTEGRATOR_H

#include "Physics/BodyList.h"
#include "Physics/ForceDriverList.h"
#include "Physics/VelocityDriverList.h"

namespace Physics {
  class Integrator {
  public:
    void integrate(BodyList &bodies);
    ForceDriverHandle createForceDriver(BodyHandle body);
    ForceDriver getForceDriver(ForceDriverHandle handle);
    VelocityDriverHandle createVelocityDriver(BodyHandle body);
  private:
    ForceDriverList forceDrivers;
    VelocityDriverList velocityDrivers;
  };
}

#endif
