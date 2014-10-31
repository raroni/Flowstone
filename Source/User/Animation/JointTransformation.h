#ifndef ANIMATION_JOINT_TRANSFORMATION_H
#define ANIMATION_JOINT_TRANSFORMATION_H

#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"

namespace Animation {
  struct JointTransformation {
    Quanta::Vector3 translation;
    Quanta::Quaternion orientation;
  };
}

#endif
