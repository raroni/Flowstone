#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "Fixie/Quaternion.h"
#include "Fixie/Vector3.h"
#include "Fixie/Matrix4.h"

namespace Physics {
  struct Body {
    Fixie::Vector3 *position;
    Fixie::Quaternion *orientation;
    Fixie::Vector3 *velocity;
  };
}

#endif
