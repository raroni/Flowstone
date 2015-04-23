#include "Fixie/Vector3.h"
#include "Physics/BodyList.h"
#include "Physics/CollisionDetector.h"
#include "Physics/CollisionSet.h"
#include "Orwell.h"

namespace CollisionDetectorTest {
  using namespace Orwell::Assertions;
  using namespace Physics;
  typedef CollisionDetector Detector;

  void setupSphereCollider(BodyList &bodies, Detector &detector, Fixie::Vector3 position, Fixie::Num radius) {
    BodyHandle bodyHandle = bodies.create();
    Body body = bodies.get(bodyHandle);
    (*body.position) = position;
    detector.createSphereCollider(bodyHandle, ColliderType::Dynamic, radius);
  }

  void testSphereCollision() {
    BodyList bodies;
    Detector detector;
    setupSphereCollider(bodies, detector, { 5, 5, 5 }, 0.5);
    setupSphereCollider(bodies, detector, { 5.1, 5.1, 5.1 }, 0.5);

    CollisionSet set;
    detector.detect(set, bodies);
    assertEqual(1, set.dynamics.getCount());
  }

  void testSphereMiss() {
    BodyList bodies;
    Detector detector;
    setupSphereCollider(bodies, detector, { -1.5, 0, 0 }, 1);
    setupSphereCollider(bodies, detector, { 1.5, 0, 0 }, 1);

    CollisionSet set;
    detector.detect(set, bodies);
    assertEqual(0, set.dynamics.getCount());
  }

  /*
  temporarily disabled due to no support for destruction
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
  */

  void testSphereSeparation() {
    BodyList bodies;
    Detector detector;
    setupSphereCollider(bodies, detector, { 0, 0, 0 }, 1);
    setupSphereCollider(bodies, detector, { 1.5, 0, 0 }, 1);

    CollisionSet set;
    detector.detect(set, bodies);

    assertEqual(1, set.dynamics.getCount());
    Fixie::Vector3 separation = set.dynamics.collisions[0].separation;
    assertInDelta(0.5, 0.01, separation[0]);
    assertInDelta(0, 0.01, separation[1]);
    assertInDelta(0, 0.01, separation[2]);
  }

  void setup() {
    unsigned group = Orwell::createGroup("CollisionDetectionTest");
    //Orwell::addTest(group, testSphereColliderDestruction, "SphereColliderDestruction");
    Orwell::addTest(group, testSphereCollision, "SphereCollision");
    Orwell::addTest(group, testSphereMiss, "SphereMiss");
    Orwell::addTest(group, testSphereSeparation, "SphereSeparation");
  }
}
