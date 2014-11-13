#ifndef RENDERING2_ANIMATED_VERTEX_H
#define RENDERING2_ANIMATED_VERTEX_H

#include <stdint.h>

namespace Rendering2 {
  struct AnimatedVertex {
    float x;
    float y;
    float z;
    uint8_t jointIndex;
  };
}

#endif
