#ifndef RENDERING_SSAO_BLUR_PASS_H
#define RENDERING_SSAO_BLUR_PASS_H

#include "Rendering/Resolution.h"

namespace Rendering {
  class CommandStream;

  namespace SSAOBlurPass {
    void initialize();
    void handleResolutionChange(Resolution resolution);
    void write(CommandStream &stream);
  }
}

#endif
