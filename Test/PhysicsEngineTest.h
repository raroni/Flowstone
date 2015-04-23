#include "Physics/Engine.h"
#include "Orwell.h"

namespace PhysicsEngineTest {
  using namespace Orwell::Assertions;
  using namespace Physics;

  void testRetrieval() {
    Engine engine;
    BodyHandle handle = engine.createBody();
    Body body1 = engine.getBody(handle);
    (*body1.velocity)[1] = 1.234;
    engine.createBody();
    Body body2 = engine.getBody(handle);
    assertInDelta(1.234, 0.01, (*body2.velocity)[1]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("PhysicsEngine");
    Orwell::addTest(group, testRetrieval, "Retrieval");
  }
}
