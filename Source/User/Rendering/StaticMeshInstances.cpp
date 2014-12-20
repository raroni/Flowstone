#include "Rendering/StaticMeshInstances.h"

namespace Rendering {
  namespace StaticMeshInstances {
    static uint16_t count = 0;
    Quanta::Matrix4 transforms[Config::maxStaticMeshInstances];
    StaticMeshIndex meshes[Config::maxStaticMeshInstances];

    StaticMeshInstanceIndex create(StaticMeshIndex mesh) {
      meshes[count] = mesh;
      transforms[count] = Quanta::Matrix4::identity();
      return count++;
    }

    void updateTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform) {
      transforms[index] = transform;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
