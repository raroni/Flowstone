#include "Orwell.h"
#include "Fixie/Num.h"

namespace FixieNumTest {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testConversion() {
    Num n;

    n = 10;
    assertEqual(10, n);

    n = 10.0;
    assertEqual(n, 10);

    n = 10.0f;
    assertEqual(n, 10);

    n = 10.99999;
    assertEqual(n, 11);
  }

  void testAddition() {
    Num a, b;

    a = 37;
    b = 3;
    assertEqual(40, a+b);

    a = -50;
    b = 3;
    assertEqual(-47, a+b);

    a = 1.7;
    b = 2.7;
    assertInDelta(4.4, 0.005, a+b);
  }

  void testSubtraction() {
    Num a, b;

    a = 37;
    b = 3;
    assertEqual(34, a-b);

    a = -50;
    b = 3;
    assertEqual(-53, a-b);

    a = -50;
    b = -3;
    assertEqual(-47, a-b);

    a = 1.7;
    b = 2.7;
    assertInDelta(-1, 0.005, a-b);
  }

  void testMultiplication() {
    Num a, b;

    a = 1.5;
    b = 3;
    assertInDelta(4.5, 0.005, a*b);

    a = 1.5;
    b = -3;
    assertInDelta(-4.5, 0.005, a*b);
  }

  void testDivision() {
    Num a, b;

    a = 1;
    b = 3;
    assertInDelta(0.33333, 0.005, a/b);

    a = 1;
    b = 2;
    assertInDelta(0.5, 0.005, a/b);
  }

  void testModulus() {
    Num a, b;

    a = 10;
    b = 3;
    assertEqual(1, a % b);

    a = 25;
    b = 5;
    assertEqual(0, a % b);

    a = 7;
    b = 16;
    assertEqual(7, a % b);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieNumTest");
    Orwell::addTest(group, testConversion, "Conversion");
    Orwell::addTest(group, testAddition, "Addition");
    Orwell::addTest(group, testSubtraction, "Subtraction");
    Orwell::addTest(group, testMultiplication, "Multiplication");
    Orwell::addTest(group, testDivision, "Division");
    Orwell::addTest(group, testModulus, "Modulus");
  }
}
