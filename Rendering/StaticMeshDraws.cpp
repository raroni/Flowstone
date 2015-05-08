#include "Rendering/StaticMeshDraws.h"

namespace Rendering {
  namespace StaticMeshDraws {
    static uint16_t count = 0;
    Quanta::Matrix4 transforms[Config::maxStaticMeshDraws];
    StaticMeshIndex meshes[Config::maxStaticMeshDraws];
    float boundingRadii[Config::maxStaticMeshDraws];

    StaticMeshDrawHandle create(StaticMeshIndex mesh, float boundingRadius) {
      meshes[count] = mesh;
      boundingRadii[count] = boundingRadius;
      transforms[count] = Quanta::Matrix4::identity();
      return count++;
    }

    void updateTransform(StaticMeshDrawHandle handle, const Quanta::Matrix4 &transform) {
      transforms[handle] = transform;
    }

    uint16_t getCount() {
      return count;
    }
  }
}
