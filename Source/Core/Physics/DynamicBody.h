#ifndef PHYSICS_DYNAMIC_BODY_H
#define PHYSICS_DYNAMIC_BODY_H

#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"

namespace Physics {
  struct DynamicBody {
    Quanta::Vector3 *position;
    Quanta::Vector3 *velocity;
    Quanta::Vector3 *force;
    Quanta::Quaternion *orientation;
  };
}

#endif
