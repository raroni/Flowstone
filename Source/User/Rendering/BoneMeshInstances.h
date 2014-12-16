#ifndef RENDERING_BONE_MESH_INSTANCES_H
#define RENDERING_BONE_MESH_INSTANCES_H

#include "Rendering/Config.h"
#include "Rendering/BoneMeshInstanceIndex.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/BoneMeshInstance.h"

namespace Rendering {
  namespace BoneMeshInstances {
    extern BoneMeshInstance list[Config::maxBoneMeshInstances];
    BoneMeshInstanceIndex create(BoneMeshIndex boneMesh, Animation::PoseIndex pose);
    void updateTransform(BoneMeshInstanceIndex index, const Quanta::Matrix4 &transform);
    uint16_t getCount();
  }
}

#endif
