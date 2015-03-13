#include "Orwell.h"
#include "CollisionDetectorTest.h"
#include "CollisionResolverTest.h"
#include "PhysicsEngineTest.h"
#include "BitSet128Test.h"
#include "BitSet32Test.h"
#include "PiperUtilTest.h"
#include "IntegratorTest.h"
#include "AckSetTest.h"

int main() {
  AckSetTest::setup();
  PiperUtilTest::setup();
  BitSet128Test::setup();
  BitSet32Test::setup();
  CollisionDetectorTest::setup();
  CollisionResolverTest::setup();
  PhysicsEngineTest::setup();
  IntegratorTest::setup();

  Orwell::start();
}
