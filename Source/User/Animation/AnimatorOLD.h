#include <assert.h>
#include <stdio.h>

namespace Animation {
  typedef uint8_t SkeletonHandle;
  typedef uint8_t AnimationHandle;

  /*
  class SkeletonInstance {
    localPose;
    globalPose;
  };
  */

  class Skeleton {

  };

  struct JointConfig {
    Vector translations;
    Quaternion orientation;
  };

  class Animator {
    const static uint8_t maxSkeletons = 20;
    const static uint8_t maxJointsPerSkeleton = 8;
    const static uint8_t maxJoints = maxSkeletons*maxJointsPerSkeleton;
    const static uint8_t maxAnimations = 40;
    const static uint8_t maxKeysPerAnimation = 4;
    const static uint8_t maxKeys = maxAnimations*maxKeysPerAnimation;
    uint8_t hierarchy[maxJoints];
    uint8_t hierarchyOffsets[maxSkeletons] = { 0 };
    uint8_t skeletonCount = 0;
    uint8_t animationSkeletonIndexes[maxAnimations];
    uint8_t skeletonLength[maxSkeletons];
    float animationDurations[maxAnimations];
    uint8_t animationCount = 0;
    float jointConfigs[maxKeys*7];
  public:
    SkeletonHandle createSkeleton(uint8_t *childJointParents, uint8_t length) {
      assert(length <= maxJointsPerSkeleton);
      size_t offset = hierarchyOffsets[skeletonCount];
      assert(offset + length < maxJoints);
      for(size_t i=0; length>i; i++) {
        hierarchy[offset+i] = childJointParents[i];
      }
      skeletonLength[skeletonCount] = length+1;
      return skeletonCount++;
    }
    AnimationHandle createAnimation(SkeletonHandle skeleton, float duration) {
      assert(animationCount < maxAnimations);
      animationSkeletonIndexes[animationCount] = skeleton;
      animationDurations[animationCount] = duration;
      return animationCount++;
    }
    void createKey(AnimationHandle animation, float offset, float *jointConfig) {
      size_t skeletonOffset = animationSkeletonIndexes[animation];
      uint8_t jointsCount = skeletonLength[skeletonOffset];
      for(uint8_t i=0; jointsCount>i; i++) {
        for(uint8_t n=0; 7>n; n++) {
          this->jointConfigs[i*7+n] = jointConfig[i*7+n];
        }
      }
    }
    void update(double timeDelta) {

    }
  };
}

/*
    uint8_t childJointParents[] = { 0, 1, 1, 0, 0 };
    Animation::SkeletonHandle skeleton = animator.createSkeleton(childJointParents, sizeof(childJointParents)/sizeof(uint8_t));

    double duration = 2.0;
    Animation::AnimationHandle idle = animator.createAnimation(skeleton, duration);
    float idleJointConfig1[] = {
      0, 0, 0, 1, 0, 0, 0, // pos xyz, rot xyzw (quat)
      0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0
    };
    animator.createKey(idle, 0, idleJointConfig1);

    animation.createKey(idleID, 0, boneConfigs);
    JointConfig idleJointConfig2 = {
      0, 0, 0, 0, 0, 0, 0,
      0, -0.1, 0, 0, 0, 0, 0, // body a bit lowered, arms should follow
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0
    };
    animation.createKey(idleID, 1.0, timeOffset2, idleJointConfig2);

    animation.createSkeletonInstance(skeletonID);
*/
