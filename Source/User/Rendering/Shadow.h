#ifndef RENDERING_SHADOW_H
#define RENDERING_SHADOW_H

#include "Quanta/Math/Matrix4.h"

namespace Rendering {
  class CommandStream;
  class BoneMeshRegistry;
  struct DrawSet;

  namespace Shadow {
    void initialize();

    void write(
      CommandStream &stream,
      const BoneMeshRegistry &boneMeshRegistry,
      const DrawSet &drawSet,
      const Quanta::Matrix4 &lightWorldViewTransform,
      const Quanta::Matrix4 &lightViewClipTransform
    );
  }
}

#endif
