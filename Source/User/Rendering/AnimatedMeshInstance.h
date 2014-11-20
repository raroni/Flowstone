#ifndef Rendering_ANIMATED_MESH_INSTANCE_H
#define Rendering_ANIMATED_MESH_INSTANCE_H

#include "Rendering/TransformIndex.h"
#include "Rendering/AnimatedMeshIndex.h"

namespace Rendering {
  struct AnimatedMeshInstance {
    AnimatedMeshIndex meshIndex;
    TransformIndex transformIndex;
  };
}

#endif
