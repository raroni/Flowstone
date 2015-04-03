#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    Client::Pose poses[Config::maxBoneMeshInstances];
    BoneMeshIndex meshes[Config::maxBoneMeshInstances];
    float boundingRadii[Config::maxBoneMeshInstances];
    Quanta::Matrix4 transforms[Config::maxBoneMeshInstances];

    BoneMeshInstanceHandle create(BoneMeshIndex mesh, float boundingRadius) {
      meshes[count] = mesh;
      transforms[count] = Quanta::Matrix4::identity();
      boundingRadii[count] = boundingRadius;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }

    BoneMeshInstance get(BoneMeshInstanceHandle handle) {
      BoneMeshInstance instance;
      instance.transform = &transforms[handle];
      instance.mesh = &meshes[handle];
      instance.pose = &poses[handle];
      return instance;
    }
  }
}
