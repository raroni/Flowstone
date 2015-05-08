#ifndef ANIMATION_ANIMATOR_H
#define ANIMATION_ANIMATOR_H

#include "Animation/Pose.h"
#include "Animation/SkeletonHandle.h"
#include "Animation/Registry.h"
#include "Animation/PoseHandle.h"

namespace Animation {
  namespace Animator {
    const Pose* getWorldPoses();
    SkeletonHandle createSkeleton(
      uint8_t *jointParentIndices,
      uint8_t jointParentIndicesLength,
      float *animationDurations,
      uint8_t *animationKeyCounts,
      uint8_t animationCount,
      float *keyTimes,
      JointConfig *jointConfigs
    );
    PoseHandle createPose(uint8_t skeletonID);
    void changeAnimation(uint8_t instanceID, uint8_t animation);
    void update(double timeDelta);
  }
}

#endif
