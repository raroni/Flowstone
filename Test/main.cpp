#include "Orwell.h"
#include "CollisionDetectorTest.h"
#include "CollisionResolverTest.h"

int main() {
  CollisionDetectorTest::setup();
  CollisionResolverTest::setup();

  Orwell::start();
}
