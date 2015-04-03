#include "Physics/Engine.h"
#include "Orwell.h"

namespace PhysicsEngineTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  void testRetrieval() {
    Engine engine;
    DynamicBodyIndex index = engine.createDynamicBody();
    DynamicBody body1 = engine.getDynamicBody(index);
    (*body1.velocity)[1] = 1.234;
    engine.createDynamicBody();
    DynamicBody body2 = engine.getDynamicBody(index);
    assertInDelta(1.234, 0.01, (*body2.velocity)[1]);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("PhysicsEngine");
    Orwell::addTest(suite, testRetrieval, "Retrieval");
  }
}
