#ifndef RENDERING_POINT_LIGHT_PASS_H
#define RENDERING_POINT_LIGHT_PASS_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Resolution.h"
#include "Rendering/PointLightDrawSet.h"

namespace Rendering {
  class CommandStream;

  namespace PointLightPass {
    void initialize();
    void write(CommandStream &stream, const PointLightDrawSet &drawSet, const Quanta::Matrix4 &cameraClipWorldTransform);
    void handleResolutionChange(Resolution resolution);
  }
}

#endif
