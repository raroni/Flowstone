#ifndef PHYSICS_STATIC_BODY_H
#define PHYSICS_STATIC_BODY_H

#include "Fixie/Vector3.h"
#include "Fixie/Quaternion.h"

namespace Physics {
  struct StaticBody {
    Fixie::Vector3 *position;
    Fixie::Quaternion *orientation;
  };
}

#endif
