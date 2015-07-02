#include <assert.h>
#include "Client/DirectionGroupList.h"

namespace Client {
  namespace DirectionGroupList {
    uint8_t count = 0;
    const uint8_t max = 8;
    uint16_t instanceOffsets[max];
    uint16_t instanceCounts[max] = { 0 };

    const uint16_t instanceAllocationMax = 256;
    uint16_t instanceAllocationCount = 0;
    Animation::PoseHandle poses[instanceAllocationMax];
    Database::EntityHandle simEntityHandles[instanceAllocationMax];

    DirectionGroupIndex create(uint8_t instanceMax) {
      assert(max != count);
      instanceOffsets[count] = instanceAllocationCount;
      instanceAllocationCount += instanceMax;
      return count++;
    }

    void addInstance(DirectionGroupIndex groupIndex, Animation::PoseHandle pose, Database::EntityHandle simEntity) {
      uint16_t instanceIndex = instanceOffsets[groupIndex] + instanceCounts[max];
      poses[instanceIndex] = pose;
      simEntityHandles[instanceIndex] = simEntity;
      instanceCounts[max]++;
    }
  }
}
