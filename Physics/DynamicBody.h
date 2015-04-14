#ifndef PHYSICS_DYNAMIC_BODY_H
#define PHYSICS_DYNAMIC_BODY_H

#include "Fixie/Vector3.h"
#include "Fixie/Quaternion.h"

namespace Physics {
  struct DynamicBody {
    Fixie::Vector3 *position;
    Fixie::Vector3 *velocity;
    Fixie::Vector3 *force;
    Fixie::Quaternion *orientation;
  };
}

#endif
