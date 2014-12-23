#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    Pose poses[Config::maxBoneMeshInstances];
    BoneMeshIndex meshes[Config::maxBoneMeshInstances];
    float boundingRadii[Config::maxBoneMeshInstances];
    Quanta::Matrix4 transforms[Config::maxBoneMeshInstances];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, float boundingRadius) {
      meshes[count] = mesh;
      transforms[count] = Quanta::Matrix4::identity();
      boundingRadii[count] = boundingRadius;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }

    BoneMeshInstance get(BoneMeshInstanceIndex index) {
      BoneMeshInstance instance;
      instance.transform = &transforms[index];
      instance.mesh = &meshes[index];
      instance.pose = &poses[index];
      return instance;
    }
  }
}
