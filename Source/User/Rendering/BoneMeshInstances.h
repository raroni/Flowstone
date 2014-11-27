#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/TransformIndex.h"
#include "Rendering/BoneMeshInstance.h"

namespace Rendering {
  namespace BoneMeshInstances {
    extern BoneMeshInstance list[256];
    BoneMeshInstanceIndex create(BoneMeshIndex boneMesh, TransformIndex transform);
    uint16_t getCount();
  }
}

#endif
