#ifndef RENDERING_DRAW_CALLS_H
#define RENDERING_DRAW_CALLS_H

#include "Rendering/BoneMeshIndex.h"

namespace Rendering {
  struct BoneMeshDrawCall {
    BoneMeshIndex mesh;
    float transform[16];
    float pose[128];
  };
}

#endif
