#ifndef RENDERING_POINT_LIGHTS_H
#define RENDERING_POINT_LIGHTS_H

#include "Quanta/Math/Vector3.h"
#include "Rendering/Config.h"
#include "Rendering/PointLightHandle.h"

namespace Rendering {
  class CommandStream;

  namespace PointLights {
    extern Quanta::Vector3 positions[Config::maxPointLights];
    extern float radii[Config::maxPointLights];

    PointLightHandle create();
    void updatePosition(PointLightHandle handle, Quanta::Vector3 position);
    uint16_t getCount();
  }
}

#endif
