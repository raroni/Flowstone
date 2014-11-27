#include <string.h>
#include "Rendering/DrawQueue.h"

namespace Rendering {
  void DrawQueue::writeType(DrawCallType type) {
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
  }
}
