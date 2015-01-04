#ifndef RENDERING_SSAO_PASS_H
#define RENDERING_SSAO_PASS_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Resolution.h"

namespace Rendering {
  class CommandStream;

  namespace SSAOPass {
    void initialize();
    void handleResolutionChange(Resolution resolution);
    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &worldViewTransform,
      const Quanta::Matrix4 &viewClipTransform,
      const Quanta::Matrix4 &clipWorldTransform
    );
  }
}

#endif
