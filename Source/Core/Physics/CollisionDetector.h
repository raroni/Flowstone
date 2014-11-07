#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/DynamicSphereColliderHandle.h"
#include "Core/Physics/FreeList.h"
#include "Quanta/Math/Vector3.h"
#include "Core/Physics/CollisionSet.h"
#include "Core/Physics/SphereColliderList.h"

namespace Physics {
  class CollisionDetector {
    SphereColliderList<DynamicSphereColliderHandle, DynamicBodyIndex> dynamicSphereColliders;
  public:
    DynamicSphereColliderHandle createDynamicSphere(DynamicBodyIndex body, float radius) {
      return dynamicSphereColliders.create(body, radius);
    }
    void destroyDynamicSphere(DynamicSphereColliderHandle handle) {
      dynamicSphereColliders.destroy(handle);
    }
    void detect(CollisionSet &set, const Quanta::Vector3 *positions) {
      detectDynamics(set.getDynamics(), positions);
      detectStatics(set.getStatics(), positions);
    }
  private:
    void detectDynamics(CollisionSet::DynamicList &collisions, const Quanta::Vector3 *positions) {
      uint8_t count = dynamicSphereColliders.getCount();
      const DynamicBodyIndex *bodyIndices = dynamicSphereColliders.getBodyIndices();
      const float *radii = dynamicSphereColliders.getRadii();
      uint8_t substart = 1;
      for(uint8_t i=0; count-1>i; i++) {
        for(uint8_t n=substart; count>n; n++) {
          DynamicBodyIndex body1 = bodyIndices[i];
          DynamicBodyIndex body2 = bodyIndices[n];
          Quanta::Vector3 difference = positions[body2]-positions[body1];
          float radiiSum = radii[i] + radii[n];
          if(difference.getSquaredLength() < radiiSum*radiiSum) {
            Quanta::Vector3 separation = difference.getNormalized()*(radiiSum-difference.getLength());
            collisions.add({
              body1,
              body2,
              separation
            });
          }
        }
        substart++;
      }
    }
    void detectStatics(CollisionSet::StaticList &collisions, const Quanta::Vector3 *positions) {
      // not impl yet
    }
  };
}
