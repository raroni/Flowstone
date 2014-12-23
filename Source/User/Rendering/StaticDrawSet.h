#ifndef RENDERING_STATIC_DRAW_SET_H
#define RENDERING_STATIC_DRAW_SET_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  struct StaticDrawSet {
    Quanta::Matrix4 transforms[Config::DrawSet::staticCount];
    StaticMeshIndex meshes[Config::DrawSet::staticCount];
    uint16_t count;
    void add(const Quanta::Matrix4 &transform, const StaticMeshIndex mesh);
  };
}

#endif
