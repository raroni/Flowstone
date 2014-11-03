#ifndef ANIMATION_ANIMATOR_H
#define ANIMATION_ANIMATOR_H

#include <assert.h>
#include "Quanta/Util.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformationFactory3D.h"
#include "Pose.h"
#include "Animation/Registry.h"

namespace Animation {
  class Animator {
    Registry registry;
    uint16_t instanceCount = 0;
    uint8_t skeletonIDs[32];
    float passed[32];
    float durations[32];
    uint8_t targetKeys[32];
    uint8_t animations[32];
    uint8_t transformationOffsets[32];
    JointTransformation originTransformations[32];
    JointTransformation currentTransformations[32];
    JointTransformation targetTransformations[32];
    Pose localPoses[32];
    Pose worldPoses[32];
    void updateLocalPoses(double timeDelta) {
      uint8_t transformationOffset = 0;
      for(uint8_t instanceIndex=0; instanceCount>instanceIndex; instanceIndex++) {
        uint8_t skeletonID = skeletonIDs[instanceIndex];
        uint8_t bonesCount = registry.getBonesCount(skeletonID);
        passed[instanceIndex] += timeDelta;
        float rest = passed[instanceIndex]-durations[instanceIndex];
        float progress = passed[instanceIndex]/durations[instanceIndex];
        progress = Quanta::min(progress, 1.0f);
        Pose *pose = &localPoses[instanceIndex];
        for(uint8_t boneIndex=0; bonesCount>boneIndex; boneIndex++) {
          JointTransformation &origin = originTransformations[transformationOffset+boneIndex];
          JointTransformation &current = currentTransformations[transformationOffset+boneIndex];
          JointTransformation &target = targetTransformations[transformationOffset+boneIndex];
          current.translation[0] = Quanta::lerp(origin.translation[0], target.translation[0], progress);
          current.translation[1] = Quanta::lerp(origin.translation[1], target.translation[1], progress);
          current.translation[2] = Quanta::lerp(origin.translation[2], target.translation[2], progress);
          // TODO: ROTATION
          pose->joints[boneIndex] = Quanta::TransformationFactory3D::translation(current.translation);
        }

        if(rest >= 0) {
          passed[instanceIndex] = rest;
          uint8_t keyCount = registry.getKeyCount(skeletonID, animations[instanceIndex]);

          if(keyCount == targetKeys[instanceIndex]+1) {
            durations[instanceIndex] = registry.getDuration(skeletonID, animations[instanceIndex]) - registry.getKeyTime(skeletonID, animations[instanceIndex], targetKeys[instanceIndex]);
            targetKeys[instanceIndex] = 0;
          } else {
            float startTime = registry.getKeyTime(skeletonID, animations[instanceIndex], targetKeys[instanceIndex]);
            float endTime = registry.getKeyTime(skeletonID, animations[instanceIndex], targetKeys[instanceIndex]+1);
            durations[instanceIndex] = endTime-startTime;
            targetKeys[instanceIndex]++;
          }

          const JointTransformation *targetTransformations = registry.getJointTransformations(skeletonID, animations[instanceIndex], targetKeys[instanceIndex]);
          for(uint8_t i=0; bonesCount>i; i++) {
            originTransformations[transformationOffset+i] = this->targetTransformations[transformationOffset+i];
            this->targetTransformations[transformationOffset+i] = targetTransformations[i];
          }

          // TODO INTERPOLATE OVER rest
        }

        transformationOffset += bonesCount;
      }
    }
    void updateGlobalPoses() {
      for(uint8_t instanceIndex=0; instanceCount>instanceIndex; instanceIndex++) {
        uint8_t skeletonID = skeletonIDs[instanceIndex];
        Pose *worldPose = &worldPoses[instanceIndex];
        Pose *localPose = &localPoses[instanceIndex];
        worldPose->joints[0] = localPoses->joints[0];
        const uint8_t *parents = registry.getJointParentIndices(skeletonID);
        uint8_t bonesCount = registry.getBonesCount(skeletonID);
        for(uint8_t i=1; bonesCount>i; i++) {
          uint8_t parentIndex = parents[i-1];
          worldPose->joints[i] = worldPose->joints[parentIndex]*localPose->joints[i];
        }
      }
    }
  public:
    const Pose* getWorldPoses() const {
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
    void createSkeletonInstance(uint8_t skeletonID) {
      skeletonIDs[instanceCount] = skeletonID;
      passed[instanceCount] = 0;
      animations[instanceCount] = 0;
      targetKeys[instanceCount] = 1;
      durations[instanceCount] = registry.getKeyTime(skeletonID, animations[instanceCount], 1);
      uint8_t bonesCount = registry.getBonesCount(skeletonID);
      uint8_t transformationOffset = transformationOffsets[instanceCount];
      transformationOffsets[instanceCount+1] = transformationOffset+bonesCount;
      const JointTransformation *transformations = registry.getJointTransformations(skeletonID, animations[instanceCount], 0);
      for(uint8_t i=0; bonesCount>i; i++) {
        originTransformations[transformationOffset+i] = transformations[i];
      }
      transformations = registry.getJointTransformations(skeletonID, animations[instanceCount], 1);
      for(uint8_t i=0; bonesCount>i; i++) {
        targetTransformations[transformationOffset+i] = transformations[i];
      }
      instanceCount++;
    }
    void changeAnimation(uint8_t instanceID, uint8_t animation) {
      passed[instanceID] = 0;
      durations[instanceID] = 0.15f;
      targetKeys[instanceID] = 0;
      animations[instanceID] = animation;
      uint8_t transformationOffset = transformationOffsets[instanceID];
      uint8_t skeletonID = skeletonIDs[instanceID];
      uint8_t bonesCount = registry.getBonesCount(skeletonID);
      const JointTransformation *targetTransformations = registry.getJointTransformations(skeletonID, animation, 0);
      for(uint8_t i=0; bonesCount>i; i++) {
        originTransformations[transformationOffset+i] = currentTransformations[transformationOffset+i];
        this->targetTransformations[transformationOffset+i] = targetTransformations[i];
      }
    }
    void update(double timeDelta) {
      updateLocalPoses(timeDelta);
      updateGlobalPoses();
    }
  };
}

#endif
