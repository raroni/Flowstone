#ifndef RENDERING_POINT_LIGHT_DRAW_SET_H
#define RENDERING_POINT_LIGHT_DRAW_SET_H

#include "Quanta/Math/Vector3.h"
#include "Rendering/Config.h"

namespace Rendering {
  struct PointLightDrawSet {
    Quanta::Vector3 positions[Config::DrawSet::pointLightCount];
    float radii[Config::DrawSet::pointLightCount];
    uint16_t count;
    void add(const Quanta::Vector3 &position, float radius);
  };
}

#endif
