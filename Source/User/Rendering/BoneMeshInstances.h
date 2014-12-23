#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/Config.h"
#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneMeshInstance.h"

namespace Rendering {
  namespace BoneMeshInstances {
    extern Pose poses[Config::maxBoneMeshInstances];
    extern BoneMeshIndex meshes[Config::maxBoneMeshInstances];
    extern float boundingRadii[Config::maxBoneMeshInstances];
    extern Quanta::Matrix4 transforms[Config::maxBoneMeshInstances];
    BoneMeshInstanceIndex create(BoneMeshIndex boneMesh, float boundingRadius);
    BoneMeshInstance get(BoneMeshInstanceIndex index);
    uint16_t getCount();
  }
}

#endif
