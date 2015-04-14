#include "Physics/CollisionDetector.h"

namespace Physics {
  static Fixie::Num differenceTolerance = 1.0/1024.0;

  void CollisionDetector::detect(CollisionSet &set, const Fixie::Vector3 *dynamicPositions, const Fixie::Vector3 *staticPositions) {
    detectDynamics(set.getDynamics(), dynamicPositions);
    detectStatics(set.getStatics(), staticPositions, dynamicPositions);
  }

  void CollisionDetector::detectDynamics(CollisionSet::DynamicList &collisions, const Fixie::Vector3 *positions) {
    uint8_t count = dynamicSphereColliders.getCount();
    const DynamicBodyIndex *bodyIndices = dynamicSphereColliders.getBodyIndices();
    const Fixie::Num *radii = dynamicSphereColliders.getRadii();
    uint8_t substart = 1;
    for(uint8_t i=0; count-1>i; i++) {
      for(uint8_t n=substart; count>n; n++) {
        DynamicBodyIndex body1 = bodyIndices[i];
        DynamicBodyIndex body2 = bodyIndices[n];
        Fixie::Vector3 difference = positions[body2]-positions[body1];
        Fixie::Num differenceSquaredLength = difference.calcSquaredLength();
        Fixie::Num radiiSum = radii[i] + radii[n];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Fixie::Vector3 separation = Fixie::Vector3::zero();
          if(differenceSquaredLength < differenceTolerance) {
            separation[0] = radiiSum;
          } else {
            Fixie::Vector3 direction = Fixie::Vector3::normalize(difference);
            separation = direction*(radiiSum-difference.calcLength());
          }
          collisions.add({
            body1,
            body2,
            separation
          });
          if(collisions.full()) return;
        }
      }
      substart++;
    }
  }

  void CollisionDetector::detectStatics(CollisionSet::StaticList &collisions, const Fixie::Vector3 *staticPositions, const Fixie::Vector3 *dynamicPositions) {
    uint8_t dynamicCount = dynamicSphereColliders.getCount();
    const DynamicBodyIndex *dynamicBodyIndices = dynamicSphereColliders.getBodyIndices();
    const Fixie::Num *dynamicRadii = dynamicSphereColliders.getRadii();

    uint8_t staticCount = staticSphereColliders.getCount();
    const StaticBodyIndex *staticBodyIndices = staticSphereColliders.getBodyIndices();
    const Fixie::Num *staticRadii = staticSphereColliders.getRadii();

    for(uint8_t d=0; dynamicCount>d; d++) {
      DynamicBodyIndex dIndex = dynamicBodyIndices[d];
      for(uint8_t s=0; staticCount>s; s++) {
        StaticBodyIndex sIndex = staticBodyIndices[s];
        Fixie::Vector3 difference = dynamicPositions[dIndex]-staticPositions[sIndex];
        Fixie::Num differenceSquaredLength = difference.calcSquaredLength();
        Fixie::Num radiiSum = dynamicRadii[d] + staticRadii[s];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Fixie::Vector3 separation = Fixie::Vector3::zero();
          if(differenceSquaredLength < differenceTolerance) {
            separation[0] = radiiSum;
          } else {
            Fixie::Vector3 direction = Fixie::Vector3::normalize(difference);
            separation = direction*(radiiSum-difference.calcLength());
          }
          collisions.add({
            sIndex,
            dIndex,
            separation
          });
          if(collisions.full()) return;
        }
      }
    }
  }
}
