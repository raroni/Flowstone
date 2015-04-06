#include "Orwell.h"
#include "Fixie/Util.h"

#include <math.h>

namespace FixieUtilTest {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testFloor() {
    Num a;

    a = Util::floor(2.5);
    assertEqual(2, a);

    a = Util::floor(9.9);
    assertEqual(9, a);

    a = Util::floor(-2.3);
    assertEqual(-3, a);
  }

  void testFmod() {
    Num a, b;

    a = 7;
    b = 3.14*2;
    assertInDelta(0.72, 0.005, Util::fmod(a, b));
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieUtilTest");
    Orwell::addTest(group, testFloor, "floor");
    Orwell::addTest(group, testFmod, "fmod");
  }
}
