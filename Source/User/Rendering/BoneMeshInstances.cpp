#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    BoneMeshInstance list[Config::maxBoneMeshInstances];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, DynamicTransformIndex transform, Animation::PoseIndex pose) {
      list[count].mesh = mesh;
      list[count].transform = transform;
      list[count].pose = pose;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
