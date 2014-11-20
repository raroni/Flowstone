#ifndef Rendering_ANIMATED_MESH_INSTANCE_H
#define Rendering_ANIMATED_MESH_INSTANCE_H

#include "Rendering/TransformIndex.h"
#include "Rendering/BoneMeshIndex.h"

namespace Rendering {
  struct BoneMeshInstance {
    BoneMeshIndex meshIndex;
    TransformIndex transformIndex;
  };
}

#endif
