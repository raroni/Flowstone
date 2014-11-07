#include "Core/Physics/DynamicBodyIndex.h"
#include "Core/Physics/DynamicSphereColliderHandle.h"
#include "Core/Physics/FreeList.h"
#include "Quanta/Math/Vector3.h"
#include "Core/Physics/CollisionSet.h"

namespace Physics {
  class CollisionDetector {
    const static uint8_t maxDynamicSpheres = 128;
    float dynamicSphereRadii[maxDynamicSpheres];
    DynamicBodyIndex dynamicSphereBodyIndices[maxDynamicSpheres];
    uint8_t dynamicSphereIndices[128];
    uint8_t dynamicSphereIDs[128];
    uint8_t dynamicSphereCount = 0;
    FreeList dynamicSphereIDPool;
  public:
    DynamicSphereColliderHandle createDynamicSphere(DynamicBodyIndex body, float radius) {
      dynamicSphereRadii[dynamicSphereCount] = radius;
      dynamicSphereBodyIndices[dynamicSphereCount] = body;
      DynamicSphereColliderHandle handle;
      handle.id = dynamicSphereIDPool.obtain();
      dynamicSphereIDs[dynamicSphereCount] = handle.id;
      dynamicSphereIndices[handle.id] = dynamicSphereCount;
      dynamicSphereCount++;
      return handle;
    }
    void destroyDynamicSphere(DynamicSphereColliderHandle handle) {
      uint8_t destroyIndex = dynamicSphereIndices[handle.id];
      uint8_t lastIndex = dynamicSphereCount-1;
      dynamicSphereRadii[destroyIndex] = dynamicSphereRadii[lastIndex];
      dynamicSphereBodyIndices[destroyIndex] = dynamicSphereBodyIndices[lastIndex];
      dynamicSphereIndices[dynamicSphereIDs[lastIndex]] = destroyIndex;
      dynamicSphereCount--;
      dynamicSphereIDPool.free(handle.id);
    }
    void detect(CollisionSet &set, const Quanta::Vector3 *positions) {
      uint8_t substart = 1;
      CollisionSet::DynamicList &dynamics = set.getDynamics();
      for(uint8_t i=0; dynamicSphereCount-1>i; i++) {
        for(uint8_t n=substart; dynamicSphereCount>n; n++) {
          DynamicBodyIndex body1 = dynamicSphereBodyIndices[i];
          DynamicBodyIndex body2 = dynamicSphereBodyIndices[n];

          Quanta::Vector3 position1 = positions[body1];
          Quanta::Vector3 position2 = positions[body2];

          Quanta::Vector3 difference = position2-position1;

          float radiiSum = dynamicSphereRadii[i] + dynamicSphereRadii[n];
          if(difference.getSquaredLength() < radiiSum*radiiSum) {
            Quanta::Vector3 separation = difference.getNormalized()*(radiiSum-difference.getLength());
            dynamics.add({
              body1,
              body2,
              separation
            });
          }
        }
        substart++;
      }
    }
  };
}
