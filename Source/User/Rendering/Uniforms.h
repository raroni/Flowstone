#ifndef RENDERING_UNIFORMS_H
#define RENDERING_UNIFORMS_H

#include "Rendering/Backend/UniformHandle.h"

namespace Rendering {
  namespace Uniforms {
    extern Backend::UniformHandle handles[32];
    void initialize();
  }
}

#endif
