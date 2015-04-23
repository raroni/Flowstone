#include "Physics/Engine.h"
#include "Orwell.h"

namespace IntegratorTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  void setupBody(BodyList &bodies, Integrator &integrator, Fixie::Vector3 position, Fixie::Vector3 velocity, Fixie::Vector3 force) {
    BodyHandle bodyHandle = bodies.create();
    Body body = bodies.get(bodyHandle);
    (*body.position) = position;
    (*body.velocity) = velocity;
    ForceDriverHandle forceDriverHandle = integrator.createForceDriver(bodyHandle);
    ForceDriver forceDriver = integrator.getForceDriver(forceDriverHandle);
    (*forceDriver.force) = force;
  }

  void testPositionChange() {
    BodyList bodies;
    Integrator integrator;
    setupBody(bodies, integrator, { 10, 0, 0 }, { 5, 0, 0 }, { 1, 0, 0 });

    integrator.integrate(bodies);

    assertInDelta(10.15045, 0.01, bodies.positions[0][0]);
    assertInDelta(0, 0.01, bodies.positions[0][1]);
    assertInDelta(0, 0.01, bodies.positions[0][2]);
  }

  void testVelocityChange() {
    BodyList bodies;
    Integrator integrator;
    setupBody(bodies, integrator, { 10, 0, 0 }, { 5, 0, 0 }, { 1, 0, 0 });

    integrator.integrate(bodies);

    assertInDelta(5.03, 0.01, bodies.velocities[0][0]);
    assertInDelta(0, 0.01, bodies.velocities[0][1]);
    assertInDelta(0, 0.01, bodies.velocities[0][2]);
  }

  void testForceReset() {
    BodyList bodies;
    Integrator integrator;
    setupBody(bodies, integrator, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 2, 3 });

    integrator.integrate(bodies);

    ForceDriver forceDriver = integrator.getForceDriver(0);

    assertEqual(0, (*forceDriver.force)[0]);
    assertEqual(0, (*forceDriver.force)[1]);
    assertEqual(0, (*forceDriver.force)[2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("Integrator");
    Orwell::addTest(group, testPositionChange, "PositionChange");
    Orwell::addTest(group, testVelocityChange, "VelocityChange");
    Orwell::addTest(group, testForceReset, "ForceReset");
  }
}
