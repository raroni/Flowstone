#include "Rendering/StaticDrawSet.h"

namespace Rendering {
  void StaticDrawSet::add(const Quanta::Matrix4 &transform, const StaticMeshIndex mesh) {
    transforms[count] = transform;
    meshes[count] = mesh;
    count++;
  }
}
