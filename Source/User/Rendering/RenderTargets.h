#ifndef RENDERING_RENDER_TARGETS_H
#define RENDERING_RENDER_TARGETS_H

#include "Rendering/Backend/RenderTargetHandle.h"

namespace Rendering {
  namespace RenderTargets {
    struct HandleList {
      Backend::RenderTargetHandle geometry;
      Backend::RenderTargetHandle shadowBase;
      Backend::RenderTargetHandle shadowBlurHorizontal;
      Backend::RenderTargetHandle shadowBlurVertical;
      Backend::RenderTargetHandle ssaoGrain;
      Backend::RenderTargetHandle ssaoBlur;
      Backend::RenderTargetHandle downsample;
    };
    extern HandleList handles;

    void initialize();
    void handleResolutionChange();
  }
}

#endif
