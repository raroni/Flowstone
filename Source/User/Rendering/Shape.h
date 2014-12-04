#ifndef RENDERING_SHAPE_H
#define RENDERING_SHAPE_H

namespace Rendering {
  struct Shape {
    Quanta::Vector3 color;
    uint8_t offset;
    uint8_t count;
  };
}

#endif
