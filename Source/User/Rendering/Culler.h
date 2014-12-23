#ifndef RENDERING_CULLER_H
#define RENDERING_CULLER_H

#include "Quanta/Geometry/Frustum.h"
#include "Quanta/Math/Matrix4.h"
#include "Rendering/Config.h"
#include "Rendering/StaticMeshInstanceIndex.h"
#include "Rendering/CullGroupIndex.h"
#include "Rendering/BoneMeshInstanceIndex.h"

namespace Rendering {
  struct CullResult;

  class Culler {
    struct Group {
      const Quanta::Matrix4 *transforms;
      const float *boundingRadii;
    };
    Group groups[Config::cullGroupsCount];
  public:
    void configureGroup(CullGroupIndex group, const Quanta::Matrix4 *transforms, const float *boundingRadii);
    void cull(const Quanta::Frustum &frustum, CullResult &result, const uint16_t *counts);
  };
}

#endif
