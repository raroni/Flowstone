#ifndef ANIMATION_JOINT_TRANSFORMATION_H
#define ANIMATION_JOINT_TRANSFORMATION_H

namespace Animation {
  struct JointTransformation {
    Quanta::Vector3 translation;
    Quanta::Quaternion orientation;
  };
}

#endif
