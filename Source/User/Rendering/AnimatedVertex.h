#ifndef Rendering_ANIMATED_VERTEX_H
#define Rendering_ANIMATED_VERTEX_H

#include <stdint.h>

namespace Rendering {
  struct AnimatedVertex {
    float x;
    float y;
    float z;
    uint8_t jointIndex;
  };
}

#endif
