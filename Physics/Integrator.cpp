#include "Fixie/Util.h"
#include "Physics/Integrator.h"

namespace Physics {
  ForceDriver Integrator::getForceDriver(ForceDriverHandle handle) {
    return forceDrivers.get(handle);
  }

  ForceDriverHandle Integrator::createForceDriver(BodyHandle handle) {
    return forceDrivers.create(handle);
  }

  VelocityDriverHandle Integrator::createVelocityDriver(BodyHandle handle) {
    return velocityDrivers.create(handle);
  }

  void Integrator::integrate(BodyList &bodies) {
    Fixie::Vector3 *positions = bodies.positions;
    Fixie::Vector3 *velocities = bodies.velocities;

    // split up into two: velocity and force
    Fixie::Num stepDuration = static_cast<Fixie::Num>(Config::stepDuration)/Fixie::Num(1000);
    Fixie::Num halfStepDuration = Fixie::Util::halve(stepDuration);
    for(uint16_t i=0; i<forceDrivers.getCount(); ++i) {
      BodyHandle bodyHandle = forceDrivers.bodyHandles[i];
      Fixie::Vector3 *force = &forceDrivers.forces[i];
      uint16_t bodyIndex = bodies.getIndex(bodyHandle);

      Fixie::Vector3 halfVelocityChange = (*force)*halfStepDuration;
      velocities[bodyIndex] += halfVelocityChange;
      positions[bodyIndex] += velocities[bodyIndex]*stepDuration;
      velocities[bodyIndex] += halfVelocityChange;
      force->reset();
    }
  }
}
