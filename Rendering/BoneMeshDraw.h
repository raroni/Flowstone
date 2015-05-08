#ifndef RENDERING_BONE_MESH_INSTANCE_H
#define RENDERING_BONE_MESH_INSTANCE_H

#include "Quanta/Math/Matrix4.h"
#include "Animation/Pose.h"
#include "Rendering/BoneMeshIndex.h"

namespace Rendering {
  struct BoneMeshDraw {
    BoneMeshIndex *mesh;
    Quanta::Matrix4 *transform;
    Animation::Pose *pose;
  };
}

#endif
