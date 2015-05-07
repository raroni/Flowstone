#include "Fixie/Util.h"
#include "Physics/Integrator.h"

namespace Physics {
  DynamicDriver Integrator::getDynamicDriver(DynamicDriverHandle handle) {
    return dynamicDrivers.get(handle);
  }

  DynamicDriverHandle Integrator::createDynamicDriver(BodyHandle handle) {
    return dynamicDrivers.create(handle);
  }

  KinematicDriverHandle Integrator::createKinematicDriver(BodyHandle handle) {
    return kinematicDrivers.create(handle);
  }

  void Integrator::integrate(BodyList &bodies) {
    Fixie::Quaternion *orientations = bodies.orientations;
    Fixie::Vector3 *spins = bodies.spins;
    Fixie::Vector3 *positions = bodies.positions;
    Fixie::Vector3 *velocities = bodies.velocities;

    // split up into two: velocity and force
    Fixie::Num stepDuration = static_cast<Fixie::Num>(Config::stepDuration)/Fixie::Num(1000);
    Fixie::Num halfStepDuration = Fixie::Util::halve(stepDuration);
    for(uint16_t i=0; i<dynamicDrivers.getCount(); ++i) {
      BodyHandle bodyHandle = dynamicDrivers.bodyHandles[i];
      uint16_t bodyIndex = bodies.getIndex(bodyHandle);

      Fixie::Vector3 *force = &dynamicDrivers.forces[i];
      Fixie::Vector3 halfVelocityChange = (*force)*halfStepDuration;
      velocities[bodyIndex] += halfVelocityChange;
      positions[bodyIndex] += velocities[bodyIndex]*stepDuration;
      velocities[bodyIndex] += halfVelocityChange;
      force->reset();

      Fixie::Vector3 *torque = &dynamicDrivers.torques[i];
      Fixie::Vector3 halfSpinChange = (*torque)*halfStepDuration;
      spins[bodyIndex] += halfSpinChange;
      static Fixie::Num half = Fixie::Num::inverse(2);
      Fixie::Quaternion spinQuaternion(0, spins[bodyIndex]);
      orientations[bodyIndex] += (spinQuaternion*orientations[bodyIndex])*half;
      orientations[bodyIndex].normalize();
      spins[bodyIndex] += halfSpinChange;
      torque->reset();
    }
  }
}
