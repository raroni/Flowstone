#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/ActionTypeList.h"
#include "Actions/StateCollection.h"

namespace Actions {
  namespace StateCollection {
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

    void* get(ActionTypeIndex typeIndex, ActionStateIndex stateIndex) {
      uint16_t offset = stateBufferOffsets[typeIndex];
      uint8_t stateLength = ActionTypeList::getStateLength(typeIndex);
      return stateBuffer + offset + stateIndex * stateLength;
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
