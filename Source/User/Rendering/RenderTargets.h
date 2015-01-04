#ifndef RENDERING_RENDER_TARGETS_H
#define RENDERING_RENDER_TARGETS_H

#include "Rendering/Backend/RenderTargetHandle.h"

namespace Rendering {
  namespace RenderTargets {
    struct HandleList {
      Backend::RenderTargetHandle geometry;
      Backend::RenderTargetHandle shadow;
      Backend::RenderTargetHandle ssao;
    };
    extern HandleList handles;

    void initialize();
  }
}

#endif
