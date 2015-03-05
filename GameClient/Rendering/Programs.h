#ifndef RENDERING_PROGRAMS_H
#define RENDERING_PROGRAMS_H

#include "SysGFX/ShaderHandle.h"

namespace Rendering {
  namespace Programs {
    struct HandleList {
      SysGFX::ShaderHandle geometryBone;
      SysGFX::ShaderHandle geometryStatic;
      SysGFX::ShaderHandle merge;
      SysGFX::ShaderHandle shadowBaseBone;
      SysGFX::ShaderHandle shadowBaseStatic;
      SysGFX::ShaderHandle shadowBlur;
      SysGFX::ShaderHandle ssaoGrain;
      SysGFX::ShaderHandle ssaoBlur;
      SysGFX::ShaderHandle downsample;
      SysGFX::ShaderHandle pointLight;
    };
    extern HandleList handles;

    void initialize();
  }
}

#endif
