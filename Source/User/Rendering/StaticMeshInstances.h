#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/Config.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticMeshInstanceIndex.h"

namespace Rendering {
  namespace StaticMeshInstances {
    extern Quanta::Matrix4 transforms[Config::maxStaticMeshInstances];
    extern StaticMeshIndex meshes[Config::maxStaticMeshInstances];
    StaticMeshInstanceIndex create(StaticMeshIndex mesh, float boundingRadius);
    void updateTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform);
    uint16_t getCount();
  }
}

#endif
