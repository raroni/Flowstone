#include "Rendering/PointLightDrawSet.h"

namespace Rendering {
  void PointLightDrawSet::add(const Quanta::Vector3 &position, float radius) {
    positions[count] = position;
    radii[count] = radius;
    count++;
  }
}
