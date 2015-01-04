#ifndef RENDERING_TEXTURES_H
#define RENDERING_TEXTURES_H

#include "Rendering/Backend/TextureHandle.h"
#include "Rendering/Resolution.h"

namespace Rendering {
  namespace Textures {
    struct List {
      Backend::TextureHandle geometryDiffuse;
      Backend::TextureHandle geometryDepth;
      Backend::TextureHandle geometryNormal;
      Backend::TextureHandle shadow;
      Backend::TextureHandle ssaoGrainResult;
      Backend::TextureHandle ssaoGrainNoise;
      Backend::TextureHandle ssaoBlur;
    };

    extern List list;

    void initialize();
    void handleResolutionChange(Resolution resolution);
  }
}

#endif
