#ifndef RENDERING_BONE_DRAW_SET_H
#define RENDERING_BONE_DRAW_SET_H

#include "Quanta/Math/Matrix4.h"
#include "Animation/Pose.h"
#include "Rendering/BoneMeshIndex.h"
#include "Rendering/Config.h"

namespace Rendering {
  struct BoneDrawSet {
    Quanta::Matrix4 transforms[Config::DrawSet::boneCount];
    BoneMeshIndex meshes[Config::DrawSet::boneCount];
    Animation::Pose poses[Config::DrawSet::boneCount];
    uint16_t count;
    void add(const Quanta::Matrix4 &transform, const BoneMeshIndex mesh, const Animation::Pose &pose);
  };
}

#endif
