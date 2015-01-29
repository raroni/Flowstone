#ifndef RENDERING_SSAO_H
#define RENDERING_SSAO_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Resolution.h"

namespace Rendering {
  class CommandStream;

  namespace SSAO {
    void initialize();
    void handleResolutionChange(Resolution resolution);
    void write(
      CommandStream &stream,
      Resolution resolution,
      const Quanta::Matrix4 &clipWorldTransform
    );
  }
}

#endif
