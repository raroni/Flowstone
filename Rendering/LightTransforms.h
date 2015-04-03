#ifndef RENDERING_LIGHT_TRANSFORMS_H
#define RENDERING_LIGHT_TRANSFORMS_H

#include "Quanta/Math/Matrix4.h"
#include "Rendering/FrustumInfo.h"

namespace Rendering {
  namespace LightTransforms {
    void calc(
      const FrustumInfo &frustumInfo,
      const Quanta::Matrix4 &cameraViewWorldTransform,
      const Quanta::Vector3 &lightDirection,
      Quanta::Matrix4 &lightWorldViewTransform,
      Quanta::Matrix4 &lightViewClipTransform
    );
  }
}

#endif
