#include "Orwell.h"
#include "CollisionDetectorTest.h"
#include "CollisionResolverTest.h"
#include "PhysicsEngineTest.h"

int main() {
  CollisionDetectorTest::setup();
  CollisionResolverTest::setup();
  PhysicsEngineTest::setup();

  Orwell::start();
}
