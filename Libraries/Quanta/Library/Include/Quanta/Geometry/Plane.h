#ifndef QUANTA_PLANE_H
#define QUANTA_PLANE_H

#include "Quanta/Math/Vector3.h"

namespace Quanta {
  struct Plane {
    Vector3 position;
    Vector3 normal;
    float calcDistance(const Quanta::Vector3 &position) const;
  };
}

#endif
