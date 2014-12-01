#ifndef RENDERING_TEXTURES_H
#define RENDERING_TEXTURES_H

#include "Rendering/Backend/TextureHandle.h"

namespace Rendering {
  namespace Textures {
    struct List {
      Backend::TextureHandle geometryDiffuse;
      Backend::TextureHandle geometryLambert;
    };

    extern List list;

    void initialize();
  }
}

#endif
