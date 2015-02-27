#ifndef RENDERING_BUFFERS_H
#define RENDERING_BUFFERS_H

#include "Rendering/Backend/BufferHandle.h"

namespace Rendering {
  namespace Buffers {
    extern Backend::BufferHandle handles[8];
    void initialize();
  }
}

#endif
