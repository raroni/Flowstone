#include "Rendering/BoneMeshInstances.h"
#include "Rendering/BoneMeshInstance.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    static BoneMeshInstance list[256];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, TransformIndex transform) {
      list[count].mesh = mesh;
      list[count].transform = transform;
      return count++;
    }
  }
}
