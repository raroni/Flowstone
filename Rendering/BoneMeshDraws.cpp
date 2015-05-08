#include "Rendering/BoneMeshDraws.h"

namespace Rendering {
  namespace BoneMeshDraws {
    static uint16_t count = 0;
    Animation::Pose poses[Config::maxBoneMeshDraws];
    BoneMeshIndex meshes[Config::maxBoneMeshDraws];
    float boundingRadii[Config::maxBoneMeshDraws];
    Quanta::Matrix4 transforms[Config::maxBoneMeshDraws];

    BoneMeshDrawHandle create(BoneMeshIndex mesh, float boundingRadius) {
      meshes[count] = mesh;
      transforms[count] = Quanta::Matrix4::identity();
      boundingRadii[count] = boundingRadius;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }

    BoneMeshDraw get(BoneMeshDrawHandle handle) {
      BoneMeshDraw draw;
      draw.transform = &transforms[handle];
      draw.mesh = &meshes[handle];
      draw.pose = &poses[handle];
      return draw;
    }
  }
}
