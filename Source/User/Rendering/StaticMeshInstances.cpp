#include "Rendering/StaticMeshInstances.h"

namespace Rendering {
  namespace StaticMeshInstances {
    static uint16_t count = 0;
    StaticMeshInstance list[Config::maxStaticMeshInstances];

    StaticMeshInstanceIndex create(StaticMeshIndex mesh) {
      list[count].mesh = mesh;
      list[count].transform = Quanta::Matrix4::identity();
      return count++;
    }

    void updateTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform) {
      list[index].transform = transform;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
