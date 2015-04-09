#include "Orwell.h"
#include "Fixie/Vector3.h"

namespace FixieVector3Test {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testInit() {
    Vector3 v1(3, 4, 5);
    assertEqual(3, v1[0]);
    assertEqual(4, v1[1]);
    assertEqual(5, v1[2]);

    Vector3 v2(1.5, 2.6, 3.7);
    assertInDelta(1.5, 0.005, v2[0]);
    assertInDelta(2.6, 0.005, v2[1]);
    assertInDelta(3.7, 0.005, v2[2]);

    Vector3 v3(Num(3), Num(4), Num(5));
    assertEqual(3, v3[0]);
    assertEqual(4, v3[1]);
    assertEqual(5, v3[2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testInit, "Init");
  }
}
