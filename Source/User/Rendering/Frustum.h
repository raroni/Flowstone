#ifndef RENDERING_FRUSTUM_H
#define RENDERING_FRUSTUM_H

namespace Quanta {
  struct Frustum;
}

namespace Rendering {
  struct FrustumInfo;

  namespace Frustum {
    void calcInfo(FrustumInfo &info);
    void calcFrustum(const FrustumInfo &info, Quanta::Frustum &frustum);
  }
}

#endif
