#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/DynamicTransformIndex.h"
#include "Rendering/BoneMeshInstance.h"

namespace Rendering {
  namespace BoneMeshInstances {
    extern BoneMeshInstance list[256];
    BoneMeshInstanceIndex create(BoneMeshIndex boneMesh, DynamicTransformIndex transform, Animation::PoseIndex pose);
    uint16_t getCount();
  }
}

#endif
