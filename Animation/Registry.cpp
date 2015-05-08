#include "Animation/Registry.h"

namespace Animation {
  uint8_t Registry::getAccumulatedKeyCount(SkeletonHandle skeleton, uint8_t animation) const {
    uint8_t animationOffset = animationOffsets[skeleton];
    uint8_t count = 0;
    for(uint8_t i=0; 100>i; i++) {
      assert(i != 100);
      if(i == animation) {
        return count;
      }
      count += animationKeyCounts[animationOffset+i];
    }
    fatalError("Could not calculate accumulated key count.");
    exit(1);
  }

  const uint8_t* Registry::getJointParentIndices(SkeletonHandle skeleton) const {
    uint8_t offset = jointParentIndicesOffsets[skeleton];
    return &jointParentIndices[offset];
  }

  float Registry::getKeyTime(SkeletonHandle skeleton, uint8_t animation, uint8_t key) const {
    uint8_t offset = keyOffsets[skeleton];
    uint8_t keyCount = getAccumulatedKeyCount(skeleton, animation);
    return keyTimes[offset+keyCount+key];
  }

  uint8_t Registry::getKeyCount(SkeletonHandle skeleton, uint8_t animation) const {
    uint8_t offset = animationOffsets[skeleton];
    return animationKeyCounts[offset+animation];
  }

  float Registry::getDuration(SkeletonHandle skeleton, uint8_t animation) {
    uint8_t offset = animationOffsets[skeleton];
    return animationDurations[offset+animation];
  }

  uint8_t Registry::getBonesCount(SkeletonHandle skeleton) const {
    return jointParentIndicesOffsets[skeleton+1]-jointParentIndicesOffsets[skeleton]+1;
  }

  const JointTransform* Registry::getJointTransforms(SkeletonHandle skeleton, uint8_t animation, uint8_t key) const {
    uint8_t offset = jointTransformOffsets[skeleton];
    uint8_t bonesCount = getBonesCount(skeleton);
    uint8_t keyCount = getAccumulatedKeyCount(skeleton, animation);
    return &jointTransforms[offset+(keyCount+key)*bonesCount];
  }

  SkeletonHandle Registry::createSkeleton(
    uint8_t *jointParentIndices,
    uint8_t jointParentIndicesLength,
    float *animationDurations,
    uint8_t *animationKeyCounts,
    uint8_t animationCount,
    float *keyTimes,
    JointConfig *jointConfigs
  ) {
    uint8_t jointParentIndicesOffset = jointParentIndicesOffsets[skeletonCount];
    jointParentIndicesOffsets[skeletonCount+1] = jointParentIndicesOffset+jointParentIndicesLength;
    for(uint8_t i=0; jointParentIndicesLength>i; i++) {
      this->jointParentIndices[jointParentIndicesOffset+i] = jointParentIndices[i];
    }

    uint8_t animationOffset = animationOffsets[skeletonCount];
    animationOffsets[skeletonCount+1] = animationOffset+animationCount;
    for(uint8_t i=0; animationCount>i; i++) {
      this->animationDurations[animationOffset+i] = animationDurations[i];
    }
    uint8_t keyCount = 0;
    for(uint8_t i=0; animationCount>i; i++) {
      this->animationKeyCounts[animationOffset+i] = animationKeyCounts[i];
      keyCount += animationKeyCounts[i];
    }

    uint8_t keyOffset = keyOffsets[skeletonCount];
    keyOffsets[skeletonCount+1] = keyOffset+keyCount;
    for(uint8_t i=0; keyCount>i; i++) {
      this->keyTimes[keyOffset+i] = keyTimes[i];
    }

    uint8_t jointTransformOffset = jointTransformOffsets[skeletonCount];
    uint8_t jointTransformCount = (jointParentIndicesLength+1)*keyCount;
    jointTransformOffsets[skeletonCount+1] = jointTransformOffset+jointTransformCount;
    for(uint8_t i=0; jointTransformCount>i; i++) {
      JointConfig *config = &jointConfigs[i];
      JointTransform *transformation = &jointTransforms[jointTransformOffset+i];
      transformation->translation[0] = config->translationX;
      transformation->translation[1] = config->translationY;
      transformation->translation[2] = config->translationZ;
      transformation->orientation.real = config->orientationW;
      transformation->orientation.imaginaries[0] = config->orientationX;
      transformation->orientation.imaginaries[1] = config->orientationY;
      transformation->orientation.imaginaries[2] = config->orientationZ;
    }

    return skeletonCount++;
  }
}
