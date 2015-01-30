#ifndef RENDERING_DRAW_SET_H
#define RENDERING_DRAW_SET_H

#include "Rendering/BoneDrawSet.h"
#include "Rendering/StaticDrawSet.h"
#include "Rendering/PointLightDrawSet.h"

namespace Rendering {
  struct DrawSet {
    BoneDrawSet boneSet;
    StaticDrawSet staticSet;
    PointLightDrawSet pointLightSet;
    void clear();
  };
}

#endif
