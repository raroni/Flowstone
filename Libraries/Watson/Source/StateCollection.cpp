#include <string.h>
#include <assert.h>
#include "Watson/Config.h"
#include "Watson/TypeList.h"
#include "Watson/StateCollection.h"

namespace Watson {
  namespace StateCollection {
    const uint16_t stateCapacity = 1024*20;
    char stateBuffer[stateCapacity];
    uint16_t stateBufferLength = 0;
    uint16_t stateBufferOffsets[Config::typeMax];

    void createList(TypeIndex typeIndex) {
      const uint16_t instanceMax = TypeList::getInstanceMax(typeIndex);
      const uint16_t stateLength = TypeList::getStateLength(typeIndex);
      const uint16_t stateBufferRequirement = instanceMax*stateLength;
      assert(stateCapacity >= stateBufferLength+stateBufferRequirement);
      stateBufferOffsets[typeIndex] = stateBufferLength;
      stateBufferLength += stateBufferRequirement;
    }

    void* getNode(TypeIndex typeIndex, uint16_t instanceIndex, NodeIndex nodeIndex) {
      const uint16_t stateLength = TypeList::getStateLength(typeIndex);
      const uint16_t bufferIndex = (
        stateBufferOffsets[typeIndex] +
        instanceIndex*stateLength +
        nodeIndex
      );
      return stateBuffer+bufferIndex;
    }

    void move(TypeIndex typeIndex, uint16_t sourceIndex, uint16_t destinationIndex) {
      void *source = getNode(typeIndex, sourceIndex, 0);
      void *destination = getNode(typeIndex, sourceIndex, 0);
      const uint16_t length = TypeList::getStateLength(typeIndex);
      memcpy(destination, source, length);
    }
  }
}
