#include <string.h>
#include "Rendering/DrawQueue.h"

namespace Rendering {
  void DrawQueue::writeType(DrawCallType type) {
    offsets[count] = position;
    count++;
    memcpy(buffer+position, &type, sizeof(type));
    position += sizeof(type);
  }

  void DrawQueue::addBoneMesh(BoneMeshDrawCall call) {
    writeType(DrawCallType::BoneMesh);
    memcpy(buffer+position, &call, sizeof(call));
    position += sizeof(call);
  }

  void DrawQueue::reset() {
    position = 0;
    count = 0;
  }

  void DrawQueue::sort() {
    // no-op for now
    // remember to adjust getBuffer() when making this
  }

  const char* DrawQueue::getBuffer(uint16_t index) const {
    return buffer + offsets[index];
  }

  uint16_t DrawQueue::getCount() const {
    return count;
  }
}
