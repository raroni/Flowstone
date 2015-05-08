#ifndef ANIMATION_POSE_H
#define ANIMATION_POSE_H

#include "Quanta/Math/Matrix4.h"

namespace Animation {
  struct Pose {
    Quanta::Matrix4 joints[8];
  };
}

#endif
