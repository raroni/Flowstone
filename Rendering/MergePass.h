#ifndef RENDERING_MERGE_PASS_H
#define RENDERING_MERGE_PASS_H

#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector3.h"
#include "Rendering/Resolution.h"

namespace Rendering {
  class CommandStream;

  namespace MergePass {
    extern Quanta::Vector3 primaryLightColor;

    void initialize();
    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &cameraClipWorldTransform,
      const Quanta::Matrix4 &lightWorldViewTransform,
      const Quanta::Matrix4 &lightViewClipTransform,
      const Quanta::Vector3 &primaryLightDirection,
      const Quanta::Vector3 &secondaryLightDirection
    );
  }
}

#endif
