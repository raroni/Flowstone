#ifndef RENDERING_RENDER_TARGETS_H
#define RENDERING_RENDER_TARGETS_H

#include "SysGFX/RenderTargetHandle.h"

namespace Rendering {
  namespace RenderTargets {
    struct HandleList {
      SysGFX::RenderTargetHandle geometry;
      SysGFX::RenderTargetHandle shadowBase;
      SysGFX::RenderTargetHandle shadowBlurHorizontal;
      SysGFX::RenderTargetHandle shadowBlurVertical;
      SysGFX::RenderTargetHandle ssaoGrain;
      SysGFX::RenderTargetHandle ssaoBlur;
      SysGFX::RenderTargetHandle downsample;
    };
    extern HandleList handles;

    void initialize();
    void handleResolutionChange();
  }
}

#endif
