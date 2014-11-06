#include "Core/Physics/TransformIndex.h"
#include "Core/Physics/SphereColliderHandle.h"
#include "Core/Physics/FreeList.h"
#include "Core/Physics/Collision.h"
#include "Quanta/Math/Vector3.h"
#include "Core/Physics/CollisionSet.h"

namespace Physics {
  class CollisionDetector {
    const static uint8_t maxSphereColliders = 128;
    float sphereColliderRadii[maxSphereColliders];
    TransformIndex sphereColliderTransformIndices[maxSphereColliders];
    uint8_t sphereColliderIndices[128];
    uint8_t sphereColliderIDs[128];
    uint8_t sphereColliderCount = 0;
    FreeList freeList;
  public:
    SphereColliderHandle createSphereCollider(TransformIndex transformIndex, float radius) {
      sphereColliderRadii[sphereColliderCount] = radius;
      sphereColliderTransformIndices[sphereColliderCount] = transformIndex;
      SphereColliderHandle handle;
      handle.id = freeList.obtain();
      sphereColliderIDs[sphereColliderCount] = handle.id;
      sphereColliderIndices[handle.id] = sphereColliderCount;
      sphereColliderCount++;
      return handle;
    }
    void destroySphereCollider(SphereColliderHandle handle) {
      uint8_t destroyIndex = sphereColliderIndices[handle.id];
      uint8_t lastIndex = sphereColliderCount-1;
      sphereColliderRadii[destroyIndex] = sphereColliderRadii[lastIndex];
      sphereColliderTransformIndices[destroyIndex] = sphereColliderTransformIndices[lastIndex];
      sphereColliderIndices[sphereColliderIDs[lastIndex]] = destroyIndex;
      sphereColliderCount--;
      freeList.free(handle.id);
    }
    void detect(CollisionSet &set, const Quanta::Vector3 *positions) {
      uint8_t substart = 1;
      for(uint8_t i=0; sphereColliderCount-1>i; i++) {
        for(uint8_t n=substart; sphereColliderCount>n; n++) {
          TransformIndex transformIndex1 = sphereColliderTransformIndices[i];
          TransformIndex transformIndex2 = sphereColliderTransformIndices[n];

          Quanta::Vector3 position1 = positions[transformIndex1];
          Quanta::Vector3 position2 = positions[transformIndex2];

          Quanta::Vector3 difference = position2-position1;

          float radiiSum = sphereColliderRadii[i] + sphereColliderRadii[n];
          if(difference.getSquaredLength() < radiiSum*radiiSum) {
            Quanta::Vector3 separation = difference.getNormalized()*(radiiSum-difference.getLength());
            set.add({
              transformIndex1,
              transformIndex2,
              separation
            });
          }
        }
        substart++;
      }
    }
  };
}
