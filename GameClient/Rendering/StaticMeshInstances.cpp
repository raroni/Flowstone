#include "Rendering/StaticMeshInstances.h"

namespace Rendering {
  namespace StaticMeshInstances {
    static uint16_t count = 0;
    Quanta::Matrix4 transforms[Config::maxStaticMeshInstances];
    StaticMeshIndex meshes[Config::maxStaticMeshInstances];
    float boundingRadii[Config::maxStaticMeshInstances];

    StaticMeshInstanceHandle create(StaticMeshIndex mesh, float boundingRadius) {
      meshes[count] = mesh;
      boundingRadii[count] = boundingRadius;
      transforms[count] = Quanta::Matrix4::identity();
      return count++;
    }

    void updateTransform(StaticMeshInstanceHandle handle, const Quanta::Matrix4 &transform) {
      transforms[handle] = transform;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
