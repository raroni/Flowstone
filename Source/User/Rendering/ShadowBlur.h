#ifndef RENDERING_SHADOW_BLUR_H
#define RENDERING_SHADOW_BLUR_H

namespace Rendering {
  class CommandStream;

  namespace ShadowBlur {
    void initialize();
    void write(CommandStream &stream);
  }
}

#endif
