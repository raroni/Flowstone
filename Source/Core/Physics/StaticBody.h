#ifndef PHYSICS_STATIC_BODY_H
#define PHYSICS_STATIC_BODY_H

#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"

namespace Physics {
  struct StaticBody {
    Quanta::Vector3 *position;
    Quanta::Quaternion *orientation;
  };
}

#endif
