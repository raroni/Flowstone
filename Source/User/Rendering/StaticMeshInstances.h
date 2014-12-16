#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Rendering/Config.h"
#include "Rendering/StaticMeshInstance.h"
#include "Rendering/StaticMeshIndex.h"
#include "Rendering/StaticMeshInstanceIndex.h"

namespace Rendering {
  namespace StaticMeshInstances {
    extern StaticMeshInstance list[Config::maxStaticMeshInstances];
    StaticMeshInstanceIndex create(StaticMeshIndex mesh);
    void updateTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform);
    uint16_t getCount();
  }
}

#endif
