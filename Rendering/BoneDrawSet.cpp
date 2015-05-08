#include "Rendering/BoneDrawSet.h"

namespace Rendering {
  void BoneDrawSet::add(const Quanta::Matrix4 &transform, const BoneMeshIndex mesh, const Animation::Pose &pose) {
    transforms[count] = transform;
    meshes[count] = mesh;
    poses[count] = pose;
    count++;
  }
}
