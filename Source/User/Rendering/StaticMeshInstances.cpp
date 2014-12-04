#include "Rendering/StaticMeshInstance.h"
#include "Rendering/StaticMeshInstances.h"

namespace Rendering {
  namespace StaticMeshInstances {
    static uint16_t count = 0;
    StaticMeshInstance list[256];

    void create(StaticMeshIndex mesh) {
      list[count].mesh = mesh;
      count++;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
