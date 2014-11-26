#ifndef RENDERING_BACKEND_BONE_VERTEX_H
#define RENDERING_BACKEND_BONE_VERTEX_H

#include <stdint.h>
#include "Quanta/Math/Vector3.h"

namespace Rendering {
  namespace Backend {
    struct BoneVertex {
      float px, py, pz;
      float nx, ny, nz;
      uint8_t jointIndex;
    };
  }
}

#endif
