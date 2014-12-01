#ifndef RENDERING_RENDER_TARGETS_H
#define RENDERING_RENDER_TARGETS_H

#include "Rendering/Backend/RenderTargetHandle.h"

namespace Rendering {
  namespace RenderTargets {
    struct {
      Backend::RenderTargetHandle geometry;
    } handles;

    void initialize();
  }
}

#endif
