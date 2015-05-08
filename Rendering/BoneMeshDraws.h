#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/Config.h"
#include "Rendering/BoneMeshDrawHandle.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneMeshDraw.h"

namespace Rendering {
  namespace BoneMeshDraws {
    extern Animation::Pose poses[Config::maxBoneMeshDraws];
    extern BoneMeshIndex meshes[Config::maxBoneMeshDraws];
    extern float boundingRadii[Config::maxBoneMeshDraws];
    extern Quanta::Matrix4 transforms[Config::maxBoneMeshDraws];
    BoneMeshDrawHandle create(BoneMeshIndex boneMesh, float boundingRadius);
    BoneMeshDraw get(BoneMeshDrawHandle handle);
    uint16_t getCount();
  }
}

#endif
