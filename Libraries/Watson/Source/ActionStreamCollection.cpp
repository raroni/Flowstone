#include <assert.h>
#include "Watson/TypeList.h"
#include "Watson/Config.h"
#include "Watson/ActionStreamCollection.h"

namespace Watson {
  namespace ActionStreamCollection {
    const uint16_t bufferCapacity = 256;
    Stream buffer[bufferCapacity];
    uint16_t bufferLength = 0;
    uint16_t offsets[Config::typeMax];

    void createList(TypeIndex typeIndex) {
      const uint16_t instanceMax = TypeList::getInstanceMax(typeIndex);
      assert(bufferCapacity >= bufferLength+instanceMax);
      offsets[typeIndex] = bufferLength;
      bufferLength += instanceMax;
    }

    Stream* get(TypeIndex typeIndex, uint16_t instanceIndex) {
      uint16_t offset = offsets[typeIndex]+instanceIndex;
      return buffer+offset;
    }

    void move(TypeIndex typeIndex, uint16_t sourceIndex, uint16_t destinationIndex) {
      uint16_t typeOffset = offsets[typeIndex];
      buffer[typeOffset+destinationIndex] = buffer[typeOffset+sourceIndex];
    }
  }
}
