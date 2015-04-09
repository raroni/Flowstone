#include "Orwell.h"
#include "Fixie/Matrix4.h"

namespace FixieMatrix4Test {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testSetGet() {
    Matrix4 m;
    m[0] = 3;
    assertEqual(3, m[0]);

    m[1] = -6;
    assertEqual(-6, m[1]);

    m[2] = 5.4;
    assertInDelta(5.4, 0.002, m[2]);

    m[3] = 0;
    assertEqual(0, m[3]);

    m[4] = Num(99);
    assertEqual(99, m[4]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testSetGet, "SetGet");
  }
}
