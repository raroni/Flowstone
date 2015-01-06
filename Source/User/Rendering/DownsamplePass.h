#ifndef RENDERING_DOWNSAMPLE_PASS_H
#define RENDERING_DOWNSAMPLE_PASS_H

namespace Rendering {
  class CommandStream;

  namespace DownsamplePass {
    void write(CommandStream &stream);
  }
}

#endif
