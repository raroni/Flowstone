#ifndef RENDERING_TEXTURES_H
#define RENDERING_TEXTURES_H

#include "Rendering/Backend/TextureHandle.h"

namespace Rendering {
  namespace Textures {
    struct List {
      Backend::TextureHandle geometryDiffuse;
      Backend::TextureHandle geometryDepth;
      Backend::TextureHandle geometryNormal;
      Backend::TextureHandle shadow;
      Backend::TextureHandle mergeNoise;
    };

    extern List list;

    void initialize();
  }
}

#endif
