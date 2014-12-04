#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Rendering/StaticMeshInstance.h"
#include "Rendering/StaticMeshIndex.h"

namespace Rendering {
  namespace StaticMeshInstances {
    extern StaticMeshInstance list[256];
    void create(StaticMeshIndex mesh);
    uint16_t getCount();
  }
}

#endif
