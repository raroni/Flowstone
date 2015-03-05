#ifndef RENDERING_BUFFERS_H
#define RENDERING_BUFFERS_H

#include "SysGFX/BufferHandle.h"

namespace Rendering {
  namespace Buffers {
    extern SysGFX::BufferHandle handles[8];
    void initialize();
  }
}

#endif
