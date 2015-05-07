#include "Orwell.h"
#include "Fixie/Vector2.h"

namespace FixieVector2Test {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testInit() {
    Vector2 v1(3, 4);
    assertEqual(3, v1[0]);
    assertEqual(4, v1[1]);

    Vector2 v2(1.5, 2.6);
    assertInDelta(1.5, 0.005, v2[0]);
    assertInDelta(2.6, 0.005, v2[1]);

    Vector2 v3(Num(3), Num(4));
    assertEqual(3, v3[0]);
    assertEqual(4, v3[1]);
  }

  void testSubtraction() {
    Vector2 v1;
    Vector2 v2;
    Vector2 sum;

    v1 = { 3, 4 };
    v2 = { 11, 6.7 };
    sum = v1-v2;
    assertEqual(-8, sum[0]);
    assertInDelta(-2.7, 0.001, sum[1]);

    v1 = { 3, 4 };
    v2 = { -3, -4 };
    sum = v1-v2;
    assertEqual(6, sum[0]);
    assertEqual(8, sum[1]);
  }

  void testLength() {
    Vector2 v;
    Num length;

    v = { 3, 2 };
    length = v.calcLength();
    assertInDelta(3.6056, 0.002, length);

    v = { -7.9, 7 };
    length = v.calcLength();
    assertInDelta(10.5551, 0.002, length);
  }

  void testSquaredLength() {
    Vector2 v;
    Num squaredLength;

    v = { 3, -4 };
    squaredLength = v.calcSquaredLength();
    assertEqual(25, squaredLength);

    v = { 4, 81 };
    squaredLength = v.calcSquaredLength();
    assertEqual(6577, squaredLength);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieVector2");
    Orwell::addTest(group, testInit, "Init");
    Orwell::addTest(group, testSubtraction, "Subtraction");
    Orwell::addTest(group, testLength, "Length");
    Orwell::addTest(group, testSquaredLength, "SquaredLength");
  }
}
