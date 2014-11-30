#ifndef RENDERING_BONE_MESH_INSTANCE_H
#define RENDERING_BONE_MESH_INSTANCE_H

#include "Animation/PoseIndex.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/TransformIndex.h"

namespace Rendering {
  struct BoneMeshInstance {
    BoneMeshIndex mesh;
    TransformIndex transform;
    Animation::PoseIndex pose;
  };
}

#endif
