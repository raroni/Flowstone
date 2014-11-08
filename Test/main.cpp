#include "Orwell.h"
#include "CollisionDetectorTest.h"
#include "CollisionResolverTest.h"
#include "PhysicsEngineTest.h"
#include "IntegratorTest.h"

int main() {
  CollisionDetectorTest::setup();
  CollisionResolverTest::setup();
  PhysicsEngineTest::setup();
  IntegratorTest::setup();

  Orwell::start();
}
