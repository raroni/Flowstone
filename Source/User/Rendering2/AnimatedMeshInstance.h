#ifndef RENDERING2_ANIMATED_MESH_INSTANCE_H
#define RENDERING2_ANIMATED_MESH_INSTANCE_H

#include "Rendering2/TransformIndex.h"
#include "Rendering2/AnimatedMeshIndex.h"

namespace Rendering2 {
  struct AnimatedMeshInstance {
    AnimatedMeshIndex meshIndex;
    TransformIndex transformIndex;
  };
}

#endif
