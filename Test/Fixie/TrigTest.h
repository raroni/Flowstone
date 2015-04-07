#include "Orwell.h"
#include "Fixie/Trig.h"

namespace FixieTrigTest {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testConstants() {
    assertInDelta(3.1415, 0.005, Trig::pi);
    assertInDelta(6.2831, 0.005, Trig::pi2);
  }

  void testSine() {
    Num n;

    n = Trig::sin(0);
    assertInDelta(0, 0.00001, n);

    n = Trig::sin(Trig::pi);
    assertInDelta(0, 0.01, n);

    n = Trig::sin(Trig::pi2);
    assertInDelta(0, 0.00001, n);

    n = Trig::sin(0.3);
    assertInDelta(0.2955, 0.01, n);

    n = Trig::sin(-0.3);
    assertInDelta(-0.2955, 0.01, n);

    n = Trig::sin(30);
    assertInDelta(-0.9880, 0.01, n);

    /*
    Todo: Let's try this after updating the sine table with
    proper values that takes rounding into account
    n = Trig::sin(-100);
    assertInDelta(-0.5064, 0.01, n);
    */
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testConstants, "Constants");
    Orwell::addTest(group, testSine, "Sine");
  }
}
