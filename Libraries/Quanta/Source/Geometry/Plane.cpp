#include "Quanta/Geometry/Plane.h"

namespace Quanta {
  float Plane::calcDistance(const Quanta::Vector3& position) const {
    return Vector3::dot(normal, position-this->position);
  }
}
