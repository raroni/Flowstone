#include "Orwell.h"
#include "CollisionDetectorTest.h"
#include "CollisionResolverTest.h"
#include "PhysicsEngineTest.h"
#include "BitSet128Test.h"
#include "IntegratorTest.h"

int main() {
  BitSet128Test::setup();
  CollisionDetectorTest::setup();
  CollisionResolverTest::setup();
  PhysicsEngineTest::setup();
  IntegratorTest::setup();

  Orwell::start();
}
