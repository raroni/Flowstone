#include <assert.h>
#include "Animation/JointConfig.h"
#include "Animation/JointTransformation.h"

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
    uint8_t jointTransformationOffsets[128];
    JointTransformation jointTransformations[128];
  public:
    const uint8_t* getJointParentIndices(uint8_t skeletonID) const {
      uint8_t offset = jointParentIndicesOffsets[skeletonID];
      return &jointParentIndices[offset];
    }
    float getKeyTime(uint8_t skeletonID, uint8_t animation, uint8_t key) const {
      uint8_t animationOffset = animationOffsets[skeletonID];
      uint8_t animationKeyOffset = 0;
      for(uint8_t i=0; 100>=i; i++) {
        if(i == animation) break;
        animationKeyOffset += animationKeyCounts[animationOffset+i];
        assert(i != 100);
      }
      uint8_t keyOffset = keyOffsets[skeletonID];
      return keyTimes[keyOffset+animationKeyOffset+key];
    }
    uint8_t getBonesCount(uint8_t skeletonID) const {
      // TODO:
      // As far as I can see we cannot implement this without one of these
      // a) making a branch/if (on whether ID is 0)
      // b) make an array of bonecounts
      assert(skeletonID == 0);
      return jointParentIndicesOffsets[1]+1;
    }
    const JointTransformation* getJointTransformations(uint8_t skeletonID, uint8_t animation, uint8_t key) const {
      uint8_t bonesCount = getBonesCount(skeletonID);
      uint8_t skeletonOffset = jointTransformationOffsets[skeletonID];

      // TODO: DRY this up (also used in getKeyTime)
      uint8_t animationOffset = 0;
      for(uint8_t i=0; 100>=i; i++) {
        if(i == animation) break;
        animationOffset += animationKeyCounts[animationOffset+i]*bonesCount;
        assert(i != 100);
      }

      return &jointTransformations[skeletonOffset+animationOffset+key*bonesCount];
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

      uint8_t jointTransformationOffset = jointTransformationOffsets[skeletonCount];
      uint8_t jointTransformationCount = (jointParentIndicesLength+1)*keyCount;
      jointTransformationOffsets[skeletonCount+1] = jointTransformationOffset+jointTransformationCount;
      for(uint8_t i=0; jointTransformationCount>i; i++) {
        JointConfig *config = &jointConfigs[i];
        JointTransformation *transformation = &jointTransformations[jointTransformationOffset+i];
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
  };
}
