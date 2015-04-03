#ifndef ANIMATION_ANIMATOR_H
#define ANIMATION_ANIMATOR_H

#include "Client/Pose.h"
#include "Animation/Registry.h"
#include "Animation/PoseIndex.h"

namespace Animation {
  class Animator {
  public:
    const Client::Pose* getWorldPoses() const;
    uint8_t createSkeleton(
      uint8_t *jointParentIndices,
      uint8_t jointParentIndicesLength,
      float *animationDurations,
      uint8_t *animationKeyCounts,
      uint8_t animationCount,
      float *keyTimes,
      JointConfig *jointConfigs
    );
    PoseIndex createPose(uint8_t skeletonID);
    void changeAnimation(uint8_t instanceID, uint8_t animation);
    void update(double timeDelta);
  private:
    Registry registry;
    uint16_t instanceCount = 0;
    uint8_t skeletonIDs[32];
    float passed[32];
    float durations[32];
    uint8_t targetKeys[32];
    uint8_t animations[32];
    uint8_t transformationOffsets[32];
    JointTransform originTransforms[32*8];
    JointTransform currentTransforms[32*8];
    JointTransform targetTransforms[32*8];
    Client::Pose localPoses[32];
    Client::Pose worldPoses[32];
    void updateLocalPoses(double timeDelta);
    void updateGlobalPoses();
  };
}

#endif
