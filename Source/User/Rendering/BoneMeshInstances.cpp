#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    BoneMeshInstance list[256];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, TransformIndex transform) {
      list[count].mesh = mesh;
      list[count].transform = transform;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
