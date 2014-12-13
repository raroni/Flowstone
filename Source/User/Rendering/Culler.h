#ifndef RENDERING_CULLER_H
#define RENDERING_CULLER_H

#include "Quanta/Geometry/Frustum.h"
#include "Quanta/Math/Matrix4.h"
#include "Rendering/Config.h"
#include "Rendering/StaticMeshInstanceIndex.h"
#include "Rendering/BoneMeshInstanceIndex.h"

namespace Rendering {
  class CullResult;

  class Culler {
    struct {
      StaticMeshInstanceIndex indices[Config::maxStaticMeshInstances];
      float radii[Config::maxStaticMeshInstances];
      uint8_t count = 0;
    } staticInstances;
    struct {
      BoneMeshInstanceIndex indices[Config::maxBoneMeshInstances];
      float radii[Config::maxBoneMeshInstances];
      uint8_t count = 0;
    } boneInstances;
    bool check(const Quanta::Frustum &frustum, const Quanta::Matrix4 &transform, float radius) const;
  public:
    void cull(const Quanta::Frustum &frustum, CullResult &result) const;
    void addStatic(StaticMeshInstanceIndex instance, float radius);
    void addBone(BoneMeshInstanceIndex instance, float radius);
    const Quanta::Matrix4* dynamicTransforms;
    const Quanta::Matrix4* staticTransforms;
  };
}

#endif
