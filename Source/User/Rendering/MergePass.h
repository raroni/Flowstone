#ifndef RENDERING_MERGE_PASS_H
#define RENDERING_MERGE_PASS_H

#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector3.h"

namespace Rendering {
  class CommandStream;

  namespace MergePass {
    void write(
      CommandStream &stream,
      Quanta::Matrix4 geometryClipWorldTransform,
      Quanta::Matrix4 lightWorldClipTransform,
      const Quanta::Vector3 &lightDirection
    );
  }
}

#endif
