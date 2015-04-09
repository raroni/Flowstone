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
    assertEqual(0, n);

    n = Trig::sin(Trig::pi);
    assertEqual(0, n);

    n = Trig::sin(Trig::pi2);
    assertEqual(0, n);

    n = Trig::sin(0.3);
    assertInDelta(0.2955, 0.01, n);

    n = Trig::sin(-0.3);
    assertInDelta(-0.2955, 0.01, n);

    n = Trig::sin(30);
    assertInDelta(-0.9880, 0.01, n);

    n = Trig::sin(-100);
    assertInDelta(0.5064, 0.01, n);
  }

  void testCosine() {
    Num n;

    n = Trig::cos(0);
    assertEqual(1, n);

    n = Trig::cos(Trig::pi);
    assertEqual(-1, n);

    n = Trig::cos(Trig::pi2);
    assertEqual(1, n);

    n = Trig::cos(0.3);
    assertInDelta(0.95533, 0.01, n);

    n = Trig::cos(-0.3);
    assertInDelta(0.95533, 0.01, n);

    n = Trig::cos(30);
    assertInDelta(0.15425, 0.01, n);

    n = Trig::cos(-122);
    assertInDelta(-0.86676, 0.01, n);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testConstants, "Constants");
    Orwell::addTest(group, testSine, "Sine");
    Orwell::addTest(group, testCosine, "Cosine");
  }
}
