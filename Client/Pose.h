#ifndef CLIENT_POSE_H
#define CLIENT_POSE_H

#include "Quanta/Math/Matrix4.h"

namespace Client {
  struct Pose {
    Quanta::Matrix4 joints[8];
  };
}

#endif
