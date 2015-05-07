#ifndef PHYSICS_INTEGRATOR_H
#define PHYSICS_INTEGRATOR_H

#include "Physics/BodyList.h"
#include "Physics/DynamicDriverList.h"
#include "Physics/KinematicDriverList.h"

namespace Physics {
  class Integrator {
  public:
    void integrate(BodyList &bodies);
    DynamicDriverHandle createDynamicDriver(BodyHandle body);
    DynamicDriver getDynamicDriver(DynamicDriverHandle handle);
    KinematicDriverHandle createKinematicDriver(BodyHandle body);
  private:
    DynamicDriverList dynamicDrivers;
    KinematicDriverList kinematicDrivers;
  };
}

#endif
