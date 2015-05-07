#include "Orwell.h"
#include "Fixie/Quaternion.h"

namespace FixieQuaternionTest {
  using namespace Orwell::Assertions;
  using namespace Fixie;

  void testInit() {
    Quaternion q(1, { 2, 3, 4 });
    assertEqual(1, q.real);
    assertEqual(2, q.imaginaries[0]);
    assertEqual(3, q.imaginaries[1]);
    assertEqual(4, q.imaginaries[2]);
  }

  void testIdentity() {
    Quaternion q = Quaternion::identity();
    assertEqual(1, q.real);
    assertEqual(0, q.imaginaries[0]);
    assertEqual(0, q.imaginaries[1]);
    assertEqual(0, q.imaginaries[2]);
  }

  void testAddition() {
    Quaternion a;
    Quaternion b;
    Quaternion result;

    a.real = 0.5;
    a.imaginaries = { 1, 4, 9 };
    b.real = -1.5;
    b.imaginaries = { 2, 3, 10 };
    result = a+b;
    assertEqual(-1, result.real);
    assertEqual(3, result.imaginaries[0]);
    assertEqual(7, result.imaginaries[1]);
    assertEqual(19, result.imaginaries[2]);

    a.real = 2;
    a.imaginaries = { -4, 3, 10 };
    b.real = 7;
    b.imaginaries = { 10, 20, -30 };
    result = a+b;
    assertEqual(9, result.real);
    assertEqual(6, result.imaginaries[0]);
    assertEqual(23, result.imaginaries[1]);
    assertEqual(-20, result.imaginaries[2]);
  }

  void testQuaternionMultiplication() {
    Quaternion a;
    Quaternion b;
    Quaternion result;

    a.real = 0.5;
    a.imaginaries = { 1, 4, 9 };
    b.real = 1.5;
    b.imaginaries = { 0.5, 3, 10 };
    result = a*b;
    assertInDelta(-101.75, 0.001, result.real);
    assertInDelta(14.75, 0.001, result.imaginaries[0]);
    assertEqual(2, result.imaginaries[1]);
    assertInDelta(19.5, 0.001, result.imaginaries[2]);

    a.real = 2;
    a.imaginaries = { 0, -2, 1 };
    b.real = -3;
    b.imaginaries = { 4, 3, -3 };
    result = a*b;
    assertEqual(3, result.real);
    assertEqual(11, result.imaginaries[0]);
    assertEqual(16, result.imaginaries[1]);
    assertEqual(-1, result.imaginaries[2]);
  }

  void testScalarMultiplication() {
    Quaternion a;
    Quaternion result;

    a.real = 0.5;
    a.imaginaries = { 1, 4, 9 };
    result = a*Num(2);
    assertEqual(1, result.real);
    assertEqual(2, result.imaginaries[0]);
    assertEqual(8, result.imaginaries[1]);
    assertEqual(18, result.imaginaries[2]);

    a.real = 2;
    a.imaginaries = { -4, 3, 10 };
    result = a*Num(-4);
    assertEqual(-8, result.real);
    assertEqual(16, result.imaginaries[0]);
    assertEqual(-12, result.imaginaries[1]);
    assertEqual(-40, result.imaginaries[2]);
  }

  void testScalarDivision() {
    Quaternion q;

    q.real = 0.5;
    q.imaginaries = { 1, 4, 9 };
    q /= Num(2);
    assertInDelta(0.25, 0.001, q.real);
    assertInDelta(0.5, 0.001, q.imaginaries[0]);
    assertEqual(2, q.imaginaries[1]);
    assertInDelta(4.5, 0.001, q.imaginaries[2]);

    q.real = 2;
    q.imaginaries = { -4, 3, 10 };
    q /= Num(-4);
    assertInDelta(-0.5, 0.001, q.real);
    assertEqual(1, q.imaginaries[0]);
    assertInDelta(-0.75, 0.001, q.imaginaries[1]);
    assertInDelta(-2.5, 0.001, q.imaginaries[2]);
  }

  void testCalcLength() {
    Quaternion a;
    Num length;

    a.real = 0.5;
    a.imaginaries = { 5, 6, -9 };
    length = a.calcLength();
    assertInDelta(11.9269, 0.001, length);

    a.real = -2;
    a.imaginaries = { 0, 20, -27 };
    length = a.calcLength();
    assertInDelta(33.6601, 0.001, length);
  }

  void testNormalization() {
    Quaternion q;

    q.real = 0.5;
    q.imaginaries = { 1, 4, 9 };
    q.normalize();
    assertInDelta(0.05044, 0.001, q.real);
    assertInDelta(0.10089, 0.001, q.imaginaries[0]);
    assertInDelta(0.40355, 0.001, q.imaginaries[1]);
    assertInDelta(0.90798, 0.001, q.imaginaries[2]);

    q.real = -2;
    q.imaginaries = { 0, 20, -27 };
    q.normalize();
    assertInDelta(-0.05942, 0.001, q.real);
    assertEqual(0, q.imaginaries[0]);
    assertInDelta(0.59418, 0.001, q.imaginaries[1]);
    assertInDelta(-0.80214, 0.001, q.imaginaries[2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("FixieQuaternion");
    Orwell::addTest(group, testInit, "Init");
    Orwell::addTest(group, testIdentity, "Identity");
    Orwell::addTest(group, testAddition, "Addition");
    Orwell::addTest(group, testQuaternionMultiplication, "QuaternionMultiplication");
    Orwell::addTest(group, testScalarMultiplication, "ScalarMultiplication");
    Orwell::addTest(group, testScalarDivision, "ScalarDivision");
    Orwell::addTest(group, testCalcLength, "CalcLength");
    Orwell::addTest(group, testNormalization, "Normalization");
  }
}
