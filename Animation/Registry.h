#ifndef ANIMATION_REGISTRY_H
#define ANIMATION_REGISTRY_H

#include <assert.h>
#include "Misc/Error.h"
#include "Animation/JointConfig.h"
#include "Animation/SkeletonHandle.h"
#include "Animation/JointTransform.h"

namespace Animation {
  class Registry {
    uint8_t skeletonCount = 0;
    uint8_t jointParentIndices[512];
    uint8_t jointParentIndicesOffsets[64];
    float animationDurations[512];
    uint8_t animationOffsets[64] = { 0 };
    uint8_t animationKeyCounts[512];
    uint8_t keyOffsets[64] = { 0 };
    float keyTimes[128];
    uint8_t jointTransformOffsets[128];
    JointTransform jointTransforms[128];
    uint8_t getAccumulatedKeyCount(SkeletonHandle skeleton, uint8_t animation) const;
  public:
    const uint8_t* getJointParentIndices(SkeletonHandle skeleton) const;
    float getKeyTime(SkeletonHandle skeleton, uint8_t animation, uint8_t key) const;
    uint8_t getKeyCount(SkeletonHandle skeleton, uint8_t animation) const;
    float getDuration(SkeletonHandle skeleton, uint8_t animation);
    uint8_t getBonesCount(SkeletonHandle skeleton) const;
    const JointTransform* getJointTransforms(SkeletonHandle skeleton, uint8_t animation, uint8_t key) const;
    SkeletonHandle createSkeleton(
      uint8_t *jointParentIndices,
      uint8_t jointParentIndicesLength,
      float *animationDurations,
      uint8_t *animationKeyCounts,
      uint8_t animationCount,
      float *keyTimes,
      JointConfig *jointConfigs
    );
  };
}

#endif
