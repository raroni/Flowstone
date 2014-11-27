#ifndef RENDERING_PROGRAMS_H
#define RENDERING_PROGRAMS_H

#include "Rendering/Backend/ShaderHandle.h"

namespace Rendering {
  namespace Programs {
    extern Backend::ShaderHandle handles[16];
    void initialize();
  }
}

#endif
