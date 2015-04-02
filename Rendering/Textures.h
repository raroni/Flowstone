#ifndef RENDERING_TEXTURES_H
#define RENDERING_TEXTURES_H

#include "SysGFX/TextureHandle.h"
#include "Rendering/Resolution.h"

namespace Rendering {
  namespace Textures {
    struct List {
      SysGFX::TextureHandle geometryAppearance;
      SysGFX::TextureHandle geometrySelfIllumination;
      SysGFX::TextureHandle geometryDepth;
      SysGFX::TextureHandle geometryNormal;
      SysGFX::TextureHandle shadowBaseBufferDepth;
      SysGFX::TextureHandle shadowVarianceDepth;
      SysGFX::TextureHandle shadowBlurVarianceDepth;
      SysGFX::TextureHandle ssaoGrainResult;
      SysGFX::TextureHandle ssaoGrainNoise;
      SysGFX::TextureHandle ssaoBlur;
      SysGFX::TextureHandle downsampleDepth;
      SysGFX::TextureHandle downsampleNormal;
    };

    extern List list;

    void initialize();
    void handleResolutionChange(Resolution resolution);
  }
}

#endif
