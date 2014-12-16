#include "Rendering/BoneMeshInstances.h"

namespace Rendering {
  namespace BoneMeshInstances {
    static uint16_t count = 0;
    BoneMeshInstance list[Config::maxBoneMeshInstances];

    BoneMeshInstanceIndex create(BoneMeshIndex mesh, Animation::PoseIndex pose) {
      list[count].mesh = mesh;
      list[count].pose = pose;
      list[count].transform = Quanta::Matrix4::identity();
      return count++;
    }

    uint16_t getCount() {
      return count;
    }

    BoneMeshInstance& get(BoneMeshInstanceIndex index) {
      return list[index];
    }
  }
}
