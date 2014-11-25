#ifndef RENDERING_BONE_VERTEX_H
#define RENDERING_BONE_VERTEX_H

#include <stdint.h>
#include "Quanta/Math/Vector3.h"

namespace Rendering {
  struct BoneVertex {
    Quanta::Vector3 position;
    uint8_t jointIndex;
  };
}

#endif
