#include "Common/Physics/CollisionDetector.h"
#include "Common/Physics/CollisionSet.h"
#include "Orwell.h"

namespace CollisionDetectorTest {
  using namespace Orwell::Assertions;
  using namespace Physics;
  typedef CollisionDetector Detector;

  void testSphereCollision() {
    Detector detector;
    detector.createDynamicSphere(0, 0.5);
    detector.createDynamicSphere(1, 0.5);
    CollisionSet set;
    Quanta::Vector3 positions[] = {
      { 5, 5, 5 },
      { 5.1, 5.1, 5.1 }
    };
    detector.detect(set, positions, {});
    assertEqual(1, set.getDynamics().getCount());
  }

  void testSphereMiss() {
    Detector detector;
    detector.createDynamicSphere(0, 1);
    detector.createDynamicSphere(1, 1);
    CollisionSet set;
    Quanta::Vector3 positions[] = {
      { -1.5, 0, 0 },
      { 1.5, 0, 0 }
    };
    detector.detect(set, positions, {});
    assertEqual(0, set.getDynamics().getCount());
  }

  void testSphereColliderDestruction() {
    Detector detector;
    detector.createDynamicSphere(0, 0.5);
    DynamicSphereColliderHandle handle = detector.createDynamicSphere(1, 0.5);
    detector.createDynamicSphere(2, 0.5);

    CollisionSet set;
    Quanta::Vector3 positions[] = {
      { -0.6, 0, 0 },
      { 0, 0, 0 },
      { 0.6, 0, 0 }
    };
    detector.detect(set, positions, {});
    assertEqual(2, set.getDynamics().getCount());

    set.clear();
    detector.destroyDynamicSphere(handle);
    detector.detect(set, positions, {});
    assertEqual(0, set.getDynamics().getCount());
  }

  void testSphereSeparation() {
    Detector detector;
    detector.createDynamicSphere(0, 1);
    detector.createDynamicSphere(1, 1);
    Quanta::Vector3 positions[] = {
      { 0, 0, 0 },
      { 1.5, 0, 0 }
    };
    CollisionSet set;
    detector.detect(set, positions, {});
    assertEqual(1, set.getDynamics().getCount());
    Quanta::Vector3 separation = set.getDynamics()[0].separation;
    assertInDelta(0.5, 0.01, separation[0]);
    assertInDelta(0, 0.01, separation[1]);
    assertInDelta(0, 0.01, separation[2]);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("CollisionDetectionTest");
    Orwell::addTest(suite, testSphereColliderDestruction, "SphereColliderDestruction");
    Orwell::addTest(suite, testSphereCollision, "SphereCollision");
    Orwell::addTest(suite, testSphereMiss, "SphereMiss");
    Orwell::addTest(suite, testSphereSeparation, "SphereSeparation");
  }
}
