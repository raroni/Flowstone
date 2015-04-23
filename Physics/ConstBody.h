#ifndef PHYSICS_CONST_BODY_H
#define PHYSICS_CONST_BODY_H

#include "Fixie/Quaternion.h"
#include "Fixie/Vector3.h"
#include "Fixie/Matrix4.h"

namespace Physics {
  struct ConstBody {
    const Fixie::Vector3 *position;
    const Fixie::Quaternion *orientation;
    const Fixie::Vector3 *velocity;
    const Fixie::Matrix4 *transform;
  };
}

#endif
