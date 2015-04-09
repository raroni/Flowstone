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

  void testAddition() {
    Vector3 v1;
    Vector3 v2;
    Vector3 sum;

    v1 = { 3, 4, 5 };
    v2 = { 11, 6.7, 1 };
    sum = v1+v2;
    assertEqual(14, sum[0]);
    assertInDelta(10.7, 0.001, sum[1]);
    assertEqual(6, sum[2]);

    v1 = { 3, 4, 5 };
    v2 = { -3, -4, -5 };
    sum = v1+v2;
    assertEqual(0, sum[0]);
    assertEqual(0, sum[1]);
    assertEqual(0, sum[2]);
  }

  void testSubtraction() {
    Vector3 v1;
    Vector3 v2;
    Vector3 sum;

    v1 = { 3, 4, 5 };
    v2 = { 11, 6.7, 1 };
    sum = v1-v2;
    assertEqual(-8, sum[0]);
    assertInDelta(-2.7, 0.001, sum[1]);
    assertEqual(4, sum[2]);

    v1 = { 3, 4, 5 };
    v2 = { -3, -4, -5 };
    sum = v1-v2;
    assertEqual(6, sum[0]);
    assertEqual(8, sum[1]);
    assertEqual(10, sum[2]);
  }

  void testDot() {
    Vector3 a;
    Vector3 b;
    Num dotProduct;

    a = { 1, 2, 3 };
    b = { 4, -5, 6 };
    dotProduct = Vector3::dot(a, b);
    assertEqual(12, dotProduct);

    a = { 2, -3, 7 };
    b = { -4, 2, -4 };
    dotProduct = Vector3::dot(a, b);
    assertEqual(-42, dotProduct);

  }

  void testCross() {
    Vector3 a;
    Vector3 b;
    Vector3 crossProduct;

    a = { 3, -3, 1 };
    b = { 4, 9, 2 };
    crossProduct = Vector3::cross(a, b);
    assertEqual(-15, crossProduct[0]);
    assertEqual(-2, crossProduct[1]);
    assertEqual(39, crossProduct[2]);

    a = { 2, 1, -3 };
    b = { 0, 4, 5 };
    crossProduct = Vector3::cross(a, b);
    assertEqual(17, crossProduct[0]);
    assertEqual(-10, crossProduct[1]);
    assertEqual(8, crossProduct[2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieTrigTest");
    Orwell::addTest(group, testInit, "Init");
    Orwell::addTest(group, testAddition, "Addition");
    Orwell::addTest(group, testSubtraction, "Subtraction");
    Orwell::addTest(group, testDot, "Dot");
    Orwell::addTest(group, testCross, "Cross");
  }
}
