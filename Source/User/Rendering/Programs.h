#ifndef RENDERING_PROGRAMS_H
#define RENDERING_PROGRAMS_H

#include "Rendering/Backend/ShaderHandle.h"

namespace Rendering {
  namespace Programs {
    struct HandleList {
      Backend::ShaderHandle geometryBone;
      Backend::ShaderHandle geometryStatic;
      Backend::ShaderHandle merge;
      Backend::ShaderHandle shadowBone;
      Backend::ShaderHandle shadowStatic;
      Backend::ShaderHandle ssaoGrain;
      Backend::ShaderHandle ssaoBlur;
      Backend::ShaderHandle downsample;
    };
    extern HandleList handles;

    void initialize();
  }
}

#endif
