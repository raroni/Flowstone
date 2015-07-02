#include <assert.h>
#include "Quanta/Util.h"
#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Animation/Registry.h"
#include "Animation/Animator.h"

namespace Animation {
  namespace Animator {
    Registry registry;
    uint16_t poseCount = 0;
    uint8_t skeletonIDs[32];
    float passed[32];
    float durations[32];
    uint8_t targetKeys[32];
    uint8_t animations[32];
    uint8_t transformationOffsets[32];
    JointTransform originTransforms[32*8];
    JointTransform currentTransforms[32*8];
    JointTransform targetTransforms[32*8];
    Pose localPoses[32];
    Pose worldPoses[32];

    void updateLocalPoses(double timeDelta) {
      uint8_t transformationOffset = 0;
      for(uint8_t poseIndex=0; poseCount>poseIndex; poseIndex++) {
        uint8_t skeletonID = skeletonIDs[poseIndex];
        uint8_t bonesCount = registry.getBonesCount(skeletonID);
        passed[poseIndex] += timeDelta;
        float rest = passed[poseIndex]-durations[poseIndex];
        float progress = passed[poseIndex]/durations[poseIndex];
        progress = Quanta::min(progress, 1.0f);
        Pose *pose = &localPoses[poseIndex];
        for(uint8_t boneIndex=0; bonesCount>boneIndex; boneIndex++) {
          JointTransform &origin = originTransforms[transformationOffset+boneIndex];
          JointTransform &current = currentTransforms[transformationOffset+boneIndex];
          JointTransform &target = targetTransforms[transformationOffset+boneIndex];
          current.translation[0] = Quanta::lerp(origin.translation[0], target.translation[0], progress);
          current.translation[1] = Quanta::lerp(origin.translation[1], target.translation[1], progress);
          current.translation[2] = Quanta::lerp(origin.translation[2], target.translation[2], progress);
          // TODO: ROTATION
          pose->joints[boneIndex] = Quanta::TransformFactory3D::translation(current.translation);
        }

        if(rest >= 0) {
          passed[poseIndex] = rest;
          uint8_t keyCount = registry.getKeyCount(skeletonID, animations[poseIndex]);

          if(keyCount == targetKeys[poseIndex]+1) {
            durations[poseIndex] = registry.getDuration(skeletonID, animations[poseIndex]) - registry.getKeyTime(skeletonID, animations[poseIndex], targetKeys[poseIndex]);
            targetKeys[poseIndex] = 0;
          } else {
            float startTime = registry.getKeyTime(skeletonID, animations[poseIndex], targetKeys[poseIndex]);
            float endTime = registry.getKeyTime(skeletonID, animations[poseIndex], targetKeys[poseIndex]+1);
            durations[poseIndex] = endTime-startTime;
            targetKeys[poseIndex]++;
          }

          const JointTransform *newTargetTransforms = registry.getJointTransforms(skeletonID, animations[poseIndex], targetKeys[poseIndex]);
          for(uint8_t i=0; bonesCount>i; i++) {
            originTransforms[transformationOffset+i] = targetTransforms[transformationOffset+i];
            targetTransforms[transformationOffset+i] = newTargetTransforms[i];
          }

          // TODO INTERPOLATE OVER rest
        }

        transformationOffset += bonesCount;
      }
    }

    void updateGlobalPoses() {
      for(uint8_t poseIndex=0; poseCount>poseIndex; poseIndex++) {
        uint8_t skeletonID = skeletonIDs[poseIndex];
        Pose *worldPose = &worldPoses[poseIndex];
        Pose *localPose = &localPoses[poseIndex];
        worldPose->joints[0] = localPoses->joints[0];
        const uint8_t *parents = registry.getJointParentIndices(skeletonID);
        uint8_t bonesCount = registry.getBonesCount(skeletonID);
        for(uint8_t i=1; bonesCount>i; i++) {
          uint8_t parentIndex = parents[i-1];
          worldPose->joints[i] = worldPose->joints[parentIndex]*localPose->joints[i];
        }
      }
    }

    const Pose* getWorldPoses() {
      return worldPoses;
    }

    SkeletonHandle createSkeleton(
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

    PoseHandle createPose(uint8_t skeletonID) {
      skeletonIDs[poseCount] = skeletonID;
      passed[poseCount] = 0;
      animations[poseCount] = 0;
      targetKeys[poseCount] = 1;
      durations[poseCount] = registry.getKeyTime(skeletonID, animations[poseCount], 1);
      uint8_t bonesCount = registry.getBonesCount(skeletonID);
      uint8_t transformationOffset = transformationOffsets[poseCount];
      transformationOffsets[poseCount+1] = transformationOffset+bonesCount;
      const JointTransform *transformations = registry.getJointTransforms(skeletonID, animations[poseCount], 0);
      for(uint8_t i=0; bonesCount>i; i++) {
        originTransforms[transformationOffset+i] = transformations[i];
      }
      transformations = registry.getJointTransforms(skeletonID, animations[poseCount], 1);
      for(uint8_t i=0; bonesCount>i; i++) {
        targetTransforms[transformationOffset+i] = transformations[i];
      }
      return poseCount++;
    }

    void changeAnimation(PoseHandle poseHandle, uint8_t animation) {
      passed[poseHandle] = 0;
      durations[poseHandle] = 0.15f;
      targetKeys[poseHandle] = 0;
      animations[poseHandle] = animation;
      uint8_t transformationOffset = transformationOffsets[poseHandle];
      uint8_t skeletonID = skeletonIDs[poseHandle];
      uint8_t bonesCount = registry.getBonesCount(skeletonID);
      const JointTransform *newTargetTransforms = registry.getJointTransforms(skeletonID, animation, 0);
      for(uint8_t i=0; bonesCount>i; i++) {
        originTransforms[transformationOffset+i] = currentTransforms[transformationOffset+i];
        targetTransforms[transformationOffset+i] = newTargetTransforms[i];
      }
    }

    void update(double timeDelta) {
      updateLocalPoses(timeDelta);
      updateGlobalPoses();
    }
  }
}
