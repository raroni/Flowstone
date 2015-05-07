#ifndef FIXIE_GEOMETRY_H
#define FIXIE_GEOMETRY_H

#include "Fixie/Vector3.h"
#include "Fixie/Quaternion.h"

namespace Fixie {
  namespace Geometry {
    Fixie::Vector3 createRotated(const Vector3 *vector, const Quaternion *rotation);
  }
}

#endif
