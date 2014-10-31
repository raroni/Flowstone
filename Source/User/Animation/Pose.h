#ifndef ANIMATION_POSE
#define ANIMATION_POSE

namespace Animation {
  struct Pose {
    Quanta::Matrix4 joints[8];
  };
};

#endif
