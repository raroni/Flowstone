#ifndef RENDERING_MERGE_PASS_H
#define RENDERING_MERGE_PASS_H

#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector3.h"

namespace Rendering {
  class CommandStream;

  namespace MergePass {
    extern Quanta::Vector3 primaryLightColor;

    void initialize();

    void write(
      CommandStream &stream,
      const Quanta::Matrix4 &cameraClipWorldTransform,
      const Quanta::Matrix4 &cameraWorldViewTransform,
      const Quanta::Matrix4 &cameraViewClipTransform,
      const Quanta::Matrix4 &lightWorldClipTransform,
      const Quanta::Vector3 &primaryLightDirection,
      const Quanta::Vector3 &secondaryLightDirection
    );
  }
}

#endif
