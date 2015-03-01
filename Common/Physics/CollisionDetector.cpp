#include "Common/Physics/CollisionDetector.h"

namespace Physics {
  void CollisionDetector::detect(CollisionSet &set, const Quanta::Vector3 *dynamicPositions, const Quanta::Vector3 *staticPositions) {
    detectDynamics(set.getDynamics(), dynamicPositions);
    detectStatics(set.getStatics(), staticPositions, dynamicPositions);
  }

  void CollisionDetector::detectDynamics(CollisionSet::DynamicList &collisions, const Quanta::Vector3 *positions) {
    uint8_t count = dynamicSphereColliders.getCount();
    const DynamicBodyIndex *bodyIndices = dynamicSphereColliders.getBodyIndices();
    const float *radii = dynamicSphereColliders.getRadii();
    uint8_t substart = 1;
    for(uint8_t i=0; count-1>i; i++) {
      for(uint8_t n=substart; count>n; n++) {
        DynamicBodyIndex body1 = bodyIndices[i];
        DynamicBodyIndex body2 = bodyIndices[n];
        Quanta::Vector3 difference = positions[body2]-positions[body1];
        float differenceSquaredLength = difference.getSquaredLength();
        float radiiSum = radii[i] + radii[n];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Quanta::Vector3 direction;
          if(differenceSquaredLength < 0.001) {
            direction[0] = 1;
          } else {
            direction = difference.getNormalized();
          }
          Quanta::Vector3 separation = direction*(radiiSum-difference.getLength());
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

  void CollisionDetector::detectStatics(CollisionSet::StaticList &collisions, const Quanta::Vector3 *staticPositions, const Quanta::Vector3 *dynamicPositions) {
    uint8_t dynamicCount = dynamicSphereColliders.getCount();
    const DynamicBodyIndex *dynamicBodyIndices = dynamicSphereColliders.getBodyIndices();
    const float *dynamicRadii = dynamicSphereColliders.getRadii();

    uint8_t staticCount = staticSphereColliders.getCount();
    const StaticBodyIndex *staticBodyIndices = staticSphereColliders.getBodyIndices();
    const float *staticRadii = staticSphereColliders.getRadii();

    for(uint8_t d=0; dynamicCount>d; d++) {
      DynamicBodyIndex dIndex = dynamicBodyIndices[d];
      for(uint8_t s=0; staticCount>s; s++) {
        StaticBodyIndex sIndex = staticBodyIndices[s];
        Quanta::Vector3 difference = dynamicPositions[dIndex]-staticPositions[sIndex];
        float differenceSquaredLength = difference.getSquaredLength();
        float radiiSum = dynamicRadii[d] + staticRadii[s];
        if(differenceSquaredLength < radiiSum*radiiSum) {
          Quanta::Vector3 direction;
          if(differenceSquaredLength < 0.001) {
            direction[0] = 1;
          } else {
            direction = difference.getNormalized();
          }
          Quanta::Vector3 separation = direction*(radiiSum-difference.getLength());
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
