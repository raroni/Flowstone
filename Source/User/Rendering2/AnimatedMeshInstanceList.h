#ifndef RENDERING2_ANIMATED_MESH_INSTANCE_LIST_H
#define RENDERING2_ANIMATED_MESH_INSTANCE_LIST_H

#include "Rendering2/AnimatedMeshInstance.h"
#include "Rendering2/AnimatedMeshInstanceIndex.h"
#include "Rendering2/AnimatedMeshIndex.h"
#include "Rendering2/TransformIndex.h"

namespace Rendering2 {
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
