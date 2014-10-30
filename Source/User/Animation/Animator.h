#include <assert.h>
#include "Quanta/Util.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformationFactory3D.h"
#include "Animation/Registry.h"

#include <stdio.h>

namespace Animation {
  class Animator {
    Registry registry;
    uint16_t instanceCount = 0;
    uint8_t skeletonIDs[32];
    float passed[32];
    float durations[32];
    uint8_t transformationOffsets[32];
    JointTransformation originTransformations[32];
    JointTransformation targetTransformations[32];
    Quanta::Matrix4 localPoses[32];
    Quanta::Matrix4 worldPoses[32];
    void updateLocalPoses(double timeDelta) {
      uint8_t transformationOffset = 0;
      JointTransformation tempTransformation;
      for(uint8_t instanceIndex=0; instanceCount>instanceIndex; instanceIndex++) {
        uint8_t bonesCount = registry.getBonesCount(skeletonIDs[instanceIndex]);
        passed[instanceIndex] += timeDelta;
        float progress = passed[instanceIndex]/durations[instanceIndex];
        for(uint8_t boneIndex=0; bonesCount>boneIndex; boneIndex++) {
          JointTransformation *origin = &originTransformations[transformationOffset+boneIndex];
          JointTransformation *target = &targetTransformations[transformationOffset+boneIndex];
          tempTransformation.translation[0] = Quanta::lerp(origin->translation[0], target->translation[0], progress);
          tempTransformation.translation[1] = Quanta::lerp(origin->translation[1], target->translation[1], progress);
          tempTransformation.translation[2] = Quanta::lerp(origin->translation[2], target->translation[2], progress);
          // TODO: ROTATION

          //printf("%f\n", tempTransformation.translation[1]);
          localPoses[instanceIndex+boneIndex] = Quanta::TransformationFactory3D::translation(tempTransformation.translation);
        }
        transformationOffset += bonesCount;
      }
      //printf("\n");
      //printf("%f\n", localPoses[1][13]);
    }
    void updateGlobalPoses() {
      uint8_t offset = 0;
      for(uint8_t instanceIndex=0; instanceCount>instanceIndex; instanceIndex++) {
        uint8_t skeletonID = skeletonIDs[instanceIndex];
        worldPoses[offset] = localPoses[offset];
        const uint8_t *parents = registry.getJointParentIndices(skeletonID);
        uint8_t bonesCount = registry.getBonesCount(skeletonID);
        for(uint8_t i=1; bonesCount>i; i++) {
          uint8_t parentIndex = parents[i-1];
          worldPoses[offset+i] = worldPoses[parentIndex]*localPoses[offset+i];
        }
        offset += bonesCount;
      }
    }
  public:
    const Quanta::Matrix4* getWorldPoses() const {
      return worldPoses;
    }
    uint8_t createSkeleton(
      uint8_t *jointParentIndices,
      uint8_t jointParentIndicesLength,
      float *animationDurations,
      uint8_t *animationKeyCounts,
      uint8_t animationCount,
      float *keyTimes,
      JointConfig *jointConfigs
    ) {
      return registry.createSkeleton(
        jointParentIndices,
        jointParentIndicesLength,
        animationDurations,
        animationKeyCounts,
        animationCount,
        keyTimes,
        jointConfigs
      );
    }
    uint8_t createSkeletonInstance(uint8_t skeletonID) {
      skeletonIDs[instanceCount] = skeletonID;
      passed[instanceCount] = 0;
      durations[instanceCount] = registry.getKeyTime(skeletonID, 0, 1);
      uint8_t bonesCount = registry.getBonesCount(skeletonID);
      uint8_t transformationOffset = transformationOffsets[instanceCount];
      transformationOffsets[instanceCount+1] = transformationOffset+bonesCount;
      const JointTransformation *transformations = registry.getJointTransformations(skeletonID, 0, 0);
      for(uint8_t i=0; bonesCount>i; i++) {
        originTransformations[transformationOffset+i] = transformations[i];
      }
      transformations = registry.getJointTransformations(skeletonID, 0, 1);
      for(uint8_t i=0; bonesCount>i; i++) {
        targetTransformations[transformationOffset+i] = transformations[i];
      }
      return instanceCount++;
    }
    void update(double timeDelta) {
      updateLocalPoses(timeDelta);
      updateGlobalPoses();
    }
  };
}
