#ifndef RENDERING_DRAW_QUEUE_H
#define RENDERING_DRAW_QUEUE_H

#include "Rendering/DrawCalls.h"
#include "Rendering/DrawCallType.h"

namespace Rendering {
  class DrawQueue {
  public:
    void addBoneMesh(BoneMeshDrawCall call);
    void reset();
    void sort();
    const char* getBuffer(uint16_t index) const;
    uint16_t getCount() const;
  private:
    char buffer[1024*10];
    uint16_t offsets[256];
    uint16_t position = 0;
    uint16_t count = 0;
    void writeType(DrawCallType type);
  };
}

#endif
