#ifndef POSE_H
#define POSE_H

#include "Quanta/Math/Matrix4.h"

struct Pose {
  Quanta::Matrix4 joints[8];
};

#endif
