#include "Core/Physics/CollisionDetector.h"
#include "Core/Physics/CollisionSet.h"
#include "Orwell.h"

namespace CollisionDetectorTest {
  using namespace Orwell::Assertions;
  using namespace Physics;
  typedef CollisionDetector Detector;

  void testSphereCollision() {
    Detector detector;
    TransformIndex index = 1;
    detector.createSphereCollider(index, 0.5);
    detector.createSphereCollider(index, 0.5);
    CollisionSet set;
    Quanta::Vector3 positions[2] = {
      { 5, 5, 5 },
      { 5.1, 5.1, 5.1 }
    };
    detector.detect(set, positions);
    assertEqual(1, set.getCount());
  }

  void testSphereMiss() {
    Detector detector;
    detector.createSphereCollider(0, 1);
    detector.createSphereCollider(1, 1);
    CollisionSet set;
    Quanta::Vector3 positions[] = {
      { -1.5, 0, 0 },
      { 1.5, 0, 0 }
    };
    detector.detect(set, positions);
    assertEqual(0, set.getCount());
  }

  void testSphereColliderDestruction() {
    Detector detector;
    detector.createSphereCollider(0, 0.5);
    SphereColliderHandle handle = detector.createSphereCollider(1, 0.5);
    detector.createSphereCollider(2, 0.5);

    CollisionSet set;
    Quanta::Vector3 positions[] = {
      { -0.6, 0, 0 },
      { 0, 0, 0 },
      { 0.6, 0, 0 }
    };
    detector.detect(set, positions);
    assertEqual(2, set.getCount());

    set.clear();
    detector.destroySphereCollider(handle);
    detector.detect(set, positions);
    assertEqual(0, set.getCount());
  }

  void testSphereSeparation() {
    Detector detector;
    detector.createSphereCollider(0, 1);
    detector.createSphereCollider(1, 1);
    Quanta::Vector3 positions[] = {
      { 0, 0, 0 },
      { 1.5, 0, 0 }
    };
    CollisionSet set;
    detector.detect(set, positions);
    assertEqual(1, set.getCount());
    Quanta::Vector3 separation = set[0].separation;
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
