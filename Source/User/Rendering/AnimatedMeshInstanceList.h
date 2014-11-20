#ifndef Rendering_ANIMATED_MESH_INSTANCE_LIST_H
#define Rendering_ANIMATED_MESH_INSTANCE_LIST_H

#include "Rendering/AnimatedMeshInstance.h"
#include "Rendering/AnimatedMeshInstanceIndex.h"
#include "Rendering/AnimatedMeshIndex.h"
#include "Rendering/TransformIndex.h"

namespace Rendering {
  class AnimatedMeshInstanceList {
  public:
    AnimatedMeshInstanceIndex create(AnimatedMeshIndex meshIndex, TransformIndex transformIndex) {
      instances[count].meshIndex = meshIndex;
      instances[count].transformIndex = transformIndex;
      return count++;
    }
    AnimatedMeshInstance& get(AnimatedMeshInstanceIndex index) {
      return instances[index];
    }
  private:
    const static uint16_t maxCount = 512;
    AnimatedMeshInstance instances[maxCount];
    uint16_t count = 0;
  };
}

#endif
