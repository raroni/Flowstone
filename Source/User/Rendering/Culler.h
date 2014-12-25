#ifndef RENDERING_CULLER_H
#define RENDERING_CULLER_H

#include "Quanta/Geometry/Frustum.h"
#include "Rendering/CullResult.h"

namespace Rendering {
  struct DrawSet;

  class Culler {
  public:
    void cull(const Quanta::Frustum &frustum, DrawSet &drawSet);
  private:
    CullResult result;
    void fillCullResult(const Quanta::Frustum &frustum);
    void fillDrawSet(DrawSet &drawSet) const;
    void cullGroup(
      const Quanta::Frustum &frustum,
      const Quanta::Matrix4 *transforms,
      const float *boundingRadii,
      uint16_t count,
      CullGroupIndex group
    );
  };
}

#endif
