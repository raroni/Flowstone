#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Config.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticMeshDrawHandle.h"

namespace Rendering {
  namespace StaticMeshDraws {
    extern Quanta::Matrix4 transforms[Config::maxStaticMeshDraws];
    extern StaticMeshIndex meshes[Config::maxStaticMeshDraws];
    extern float boundingRadii[Config::maxStaticMeshDraws];
    StaticMeshDrawHandle create(StaticMeshIndex mesh, float boundingRadius);
    void updateTransform(StaticMeshDrawHandle handle, const Quanta::Matrix4 &transform);
    uint16_t getCount();
  }
}

#endif
