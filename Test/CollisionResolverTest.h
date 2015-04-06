#include "Physics/CollisionResolver.h"
#include "Physics/CollisionSet.h"
#include "Orwell.h"

namespace CollisionResolverTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  void testDynamicPositionResolution() {
    CollisionSet set;
    set.getDynamics().add({ 0, 1, { 0.5, 0, 0 } });
    Quanta::Vector3 positions[] = {
      { 0, 0, 0 },
      { 1.75, 0, 0 }
    };
    Quanta::Vector3 velocities[] = {
      { 0, 0, 0 },
      { 0, 0, 0 }
    };
    resolveCollisions(set, positions, velocities);
    assertInDelta(positions[0][0], 0.01, -0.25);
    assertInDelta(positions[0][1], 0.01, 0);
    assertInDelta(positions[0][2], 0.01, 0);
    assertInDelta(positions[1][0], 0.01, 2.0);
    assertInDelta(positions[1][1], 0.01, 0);
    assertInDelta(positions[1][2], 0.01, 0);
  }

  void setup() {
    unsigned group = Orwell::createGroup("CollisionResolverTest");
    Orwell::addTest(group, testDynamicPositionResolution, "DynamicPositionResolution");
  }
}
