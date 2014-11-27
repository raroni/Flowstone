#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/TransformIndex.h"

namespace Rendering {
  namespace BoneMeshInstances {
    BoneMeshInstanceIndex create(BoneMeshIndex boneMesh, TransformIndex transform);
  }
}

#endif
