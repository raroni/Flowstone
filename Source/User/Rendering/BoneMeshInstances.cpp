#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    BoneMeshInstance list[256];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, TransformIndex transform, Animation::PoseIndex pose) {
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
