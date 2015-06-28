#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/ActionTypeList.h"
#include "Actions/ActionStateCollection.h"

namespace Actions {
  namespace ActionStateCollection {
    HandleList handleLists[Config::actionTypeMax];

    const uint16_t pairCapacity = 1024;
    uint16_t indexBuffer[pairCapacity];
    ActionStateHandle handleBuffer[pairCapacity];
    uint16_t pairLength = 0;

    const uint16_t stateBufferCapacity = 1024*50;
    char stateBuffer[stateBufferCapacity];
    uint16_t stateBufferLength = 0;

    uint16_t stateBufferOffsets[Config::actionTypeMax];

    void createList(ActionTypeIndex index) {
      uint8_t stateLength = ActionTypeList::getStateLength(index);
      uint8_t instanceMax = ActionTypeList::getInstanceMax(index);
      uint16_t stateBufferIncrement = stateLength*instanceMax;

      assert(pairCapacity >= pairLength+instanceMax);
      assert(stateBufferCapacity >= stateBufferLength+stateBufferIncrement);

      handleLists[index].configure(
        instanceMax,
        indexBuffer+pairLength,
        handleBuffer+pairLength
      );
      pairLength += instanceMax;

      stateBufferOffsets[index] = stateBufferLength;
      stateBufferLength += stateBufferIncrement;
    }

    void* getNodeState(ActionTypeIndex typeIndex, ActionStateIndex stateIndex, NodeIndex nodeIndex) {
      uint8_t stateLength = ActionTypeList::getStateLength(typeIndex);

      uint16_t typeOffset = stateBufferOffsets[typeIndex];
      uint16_t stateOffset = stateIndex*stateLength;
      uint16_t nodeOffset = ActionTypeList::getNodeStateOffset(typeIndex, nodeIndex);

      uint16_t offset = typeOffset+stateOffset+nodeOffset;
      return stateBuffer+offset;
    }

    ActionStateHandle createInstance(ActionTypeIndex typeIndex) {
      uint16_t stateIndex;
      ActionStateHandle stateHandle;
      handleLists[typeIndex].create(&stateIndex, &stateHandle);
      return stateHandle;
    }

    ActionStateIndex getIndex(ActionTypeIndex typeIndex, ActionStateHandle stateHandle) {
      return handleLists[typeIndex].getIndex(stateHandle);
    }
  }
}
