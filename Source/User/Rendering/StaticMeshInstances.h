#ifndef RENDERING_STATIC_MESH_INSTANCES_H
#define RENDERING_STATIC_MESH_INSTANCES_H

#include "Rendering/Config.h"
#include "Rendering/StaticTransformIndex.h"
#include "Rendering/StaticMeshInstance.h"
#include "Rendering/StaticMeshIndex.h"

namespace Rendering {
  namespace StaticMeshInstances {
    extern StaticMeshInstance list[Config::maxStaticMeshInstances];
    void create(StaticMeshIndex mesh, StaticTransformIndex transform);
    uint16_t getCount();
  }
}

#endif
