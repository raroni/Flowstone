#include "Physics/CollisionResolver.h"
#include "Physics/CollisionSet.h"
#include "Orwell.h"

namespace CollisionResolverTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  BodyHandle setupBody(BodyList &bodies, Fixie::Vector3 position) {
    BodyHandle bodyHandle = bodies.create();
    Body body = bodies.get(bodyHandle);
    (*body.position) = position;
    return bodyHandle;
  }

  void testDynamicPositionResolution() {
    BodyList bodies;
    BodyHandle bodyA = setupBody(bodies, { 0, 0, 0 });
    BodyHandle bodyB = setupBody(bodies, { 1.75, 0, 0 });
    CollisionSet set;
    Fixie::Vector3 separation(0.5, 0, 0);
    set.dynamics.add(bodyA, bodyB, separation);
    resolveCollisions(set, bodies);
    assertInDelta(bodies.positions[0][0], 0.01, -0.25);
    assertInDelta(bodies.positions[0][1], 0.01, 0);
    assertInDelta(bodies.positions[0][2], 0.01, 0);
    assertInDelta(bodies.positions[1][0], 0.01, 2.0);
    assertInDelta(bodies.positions[1][1], 0.01, 0);
    assertInDelta(bodies.positions[1][2], 0.01, 0);
  }

  void setup() {
    unsigned group = Orwell::createGroup("CollisionResolverTest");
    Orwell::addTest(group, testDynamicPositionResolution, "DynamicPositionResolution");
  }
}
