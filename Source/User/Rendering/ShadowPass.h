#ifndef RENDERING_SHADOW_MAP_H
#define RENDERING_SHADOW_MAP_H

#include "Quanta/Math/Matrix4.h"

namespace Rendering {
  class CommandStream;
  class BoneMeshRegistry;
  struct DrawSet;

  namespace ShadowPass {
    void write(
      CommandStream &stream,
      const BoneMeshRegistry &boneMeshRegistry,
      const DrawSet &drawSet,
      const Quanta::Matrix4 &lightViewClipTransform,
      const Quanta::Matrix4 &lightWorldViewTransform
    );
  }
}

#endif
