#include "Rendering/PointLights.h"

namespace Rendering {
  namespace PointLights {
    Quanta::Vector3 positions[Config::maxPointLights];
    float radii[Config::maxPointLights];
    uint8_t count = 0;

    void updatePosition(PointLightHandle handle, Quanta::Vector3 position) {
      positions[handle] = position;
    }

    PointLightHandle create() {
      positions[count] = Quanta::Vector3::zero();
      radii[count] = 3;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
