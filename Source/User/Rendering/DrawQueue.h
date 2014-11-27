#ifndef RENDERING_DRAW_QUEUE_H
#define RENDERING_DRAW_QUEUE_H

#include "Rendering/DrawCalls.h"
#include "Rendering/DrawCallType.h"

namespace Rendering {
  class DrawQueue {
  public:
    void addBoneMesh(BoneMeshDrawCall call);
    void reset();
  private:
    char buffer[1024*10];
    uint16_t position = 0;
    uint16_t count = 0;
    void writeType(DrawCallType type);
  };
}

#endif
