#include "Physics/Engine.h"
#include "Orwell.h"

namespace IntegratorTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  void testPositionChange() {
    Integrator integrator;
    integrator.activate(0);
    Quanta::Vector3 positions[] = {{ 10, 0, 0 }};
    Quanta::Vector3 velocities[] = {{ 5, 0, 0 }};
    Quanta::Vector3 forces[] = {{ 1, 0, 0 }};
    integrator.integrate(positions, velocities, forces);

    assertInDelta(10.15045, 0.01, positions[0][0]);
    assertInDelta(0, 0.01, positions[0][1]);
    assertInDelta(0, 0.01, positions[0][2]);
  }

  void testVelocityChange() {
    Integrator integrator;
    integrator.activate(0);
    Quanta::Vector3 positions[] = {{ 10, 0, 0 }};
    Quanta::Vector3 velocities[] = {{ 5, 0, 0 }};
    Quanta::Vector3 forces[] = {{ 1, 0, 0 }};
    integrator.integrate(positions, velocities, forces);

    assertInDelta(5.03, 0.01, velocities[0][0]);
    assertInDelta(0, 0.01, velocities[0][1]);
    assertInDelta(0, 0.01, velocities[0][2]);
  }

  void testForceReset() {
    Integrator integrator;
    integrator.activate(0);
    Quanta::Vector3 positions[] = {{ 0, 0, 0 }};
    Quanta::Vector3 velocities[] = {{ 0, 0, 0 }};
    Quanta::Vector3 forces[] = {{ 1, 2, 3 }};
    integrator.integrate(positions, velocities, forces);

    assertInDelta(0, 0.01, forces[0][0]);
    assertInDelta(0, 0.01, forces[0][1]);
    assertInDelta(0, 0.01, forces[0][2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("Integrator");
    Orwell::addTest(group, testPositionChange, "PositionChange");
    Orwell::addTest(group, testVelocityChange, "VelocityChange");
    Orwell::addTest(group, testForceReset, "ForceReset");
  }
}
