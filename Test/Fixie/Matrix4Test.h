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

  void testIdentity() {
    Matrix4 m = Matrix4::identity();
    assertEqual(1, m[0]);
    assertEqual(0, m[1]);
    assertEqual(0, m[2]);
    assertEqual(0, m[3]);
    assertEqual(0, m[4]);
    assertEqual(1, m[5]);
    assertEqual(0, m[6]);
    assertEqual(0, m[7]);
    assertEqual(0, m[8]);
    assertEqual(0, m[9]);
    assertEqual(1, m[10]);
    assertEqual(0, m[11]);
    assertEqual(0, m[12]);
    assertEqual(0, m[13]);
    assertEqual(0, m[14]);
    assertEqual(1, m[15]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testSetGet, "SetGet");
    Orwell::addTest(group, testIdentity, "Identity");
  }
}
