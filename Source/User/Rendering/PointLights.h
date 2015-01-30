#ifndef RENDERING_POINT_LIGHTS_H
#define RENDERING_POINT_LIGHTS_H

#include "Quanta/Math/Vector3.h"
#include "Rendering/Resolution.h"
#include "Rendering/Config.h"
#include "Rendering/PointLightDrawSet.h"
#include "Rendering/PointLightIndex.h"

namespace Rendering {
  class CommandStream;

  namespace PointLights {
    extern Quanta::Vector3 positions[Config::maxPointLights];
    extern float radii[Config::maxPointLights];

    void initialize();
    void write(CommandStream &stream, const PointLightDrawSet &drawSet, const Quanta::Matrix4 &cameraClipWorldTransform);
    PointLightIndex create();
    void updatePosition(PointLightIndex index, Quanta::Vector3 position);
    void handleResolutionChange(Resolution resolution);
    uint16_t getCount();
  }
}

#endif
