#include "Rendering/StaticMeshInstances.h"

namespace Rendering {
  namespace StaticMeshInstances {
    static uint16_t count = 0;
    StaticMeshInstance list[256];

    void create(StaticMeshIndex mesh, StaticTransformIndex transform) {
      list[count].mesh = mesh;
      list[count].transform = transform;
      count++;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
