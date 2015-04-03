#ifndef ANIMATION_REGISTRY_H
#define ANIMATION_REGISTRY_H

#include <assert.h>
#include "Misc/Error.h"
#include "Animation/JointConfig.h"
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
    uint8_t getAccumulatedKeyCount(uint8_t skeletonID, uint8_t animation) const;
  public:
    const uint8_t* getJointParentIndices(uint8_t skeletonID) const;
    float getKeyTime(uint8_t skeletonID, uint8_t animation, uint8_t key) const;
    uint8_t getKeyCount(uint8_t skeletonID, uint8_t animation) const;
    float getDuration(uint8_t skeletonID, uint8_t animation);
    uint8_t getBonesCount(uint8_t skeletonID) const;
    const JointTransform* getJointTransforms(uint8_t skeletonID, uint8_t animation, uint8_t key) const;
    uint8_t createSkeleton(
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
