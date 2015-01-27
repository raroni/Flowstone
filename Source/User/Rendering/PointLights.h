#ifndef RENDERING_POINT_LIGHTS_H
#define RENDERING_POINT_LIGHTS_H

#include "Quanta/Math/Vector3.h"
#include "Rendering/PointLightIndex.h"

namespace Rendering {
  class CommandStream;

  namespace PointLights {
    void initialize();
    void write(CommandStream &stream, const Quanta::Matrix4 &cameraClipWorldTransform);
    PointLightIndex create();
    void updatePosition(PointLightIndex index, Quanta::Vector3 position);
    void handleResolutionChange(Resolution resolution);
  }
}

#endif
