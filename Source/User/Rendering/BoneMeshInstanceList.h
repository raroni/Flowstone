#ifndef Rendering_ANIMATED_MESH_INSTANCE_LIST_H
#define Rendering_ANIMATED_MESH_INSTANCE_LIST_H

#include "Rendering/BoneMeshInstance.h"
#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/TransformIndex.h"

namespace Rendering {
  class BoneMeshInstanceList {
  public:
    BoneMeshInstanceIndex create(BoneMeshIndex meshIndex, TransformIndex transformIndex) {
      instances[count].meshIndex = meshIndex;
      instances[count].transformIndex = transformIndex;
      return count++;
    }
    BoneMeshInstance& get(BoneMeshInstanceIndex index) {
      return instances[index];
    }
  private:
    const static uint16_t maxCount = 512;
    BoneMeshInstance instances[maxCount];
    uint16_t count = 0;
  };
}

#endif
