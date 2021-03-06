#include <assert.h>
#include "Actions/ExecutionList.h"

namespace Actions {
  namespace ExecutionList {
    const uint8_t actionStateLengthMax = 16;
    struct ActionStateChunk {
      char bytes[actionStateLengthMax];
    };
    const uint16_t max = 128;
    InstanceHandle instanceHandles[max];
    ActionStateChunk actionStateChunks[max];
    uint16_t count = 0;

    uint16_t create(InstanceHandle handle, uint8_t actionStateLength) {
      assert(count != max);
      assert(actionStateLengthMax >= actionStateLength);
      instanceHandles[count] = handle;
      return count++;
    }

    uint16_t getCount() {
      return count;
    }

    InstanceHandle getInstanceHandle(uint16_t index) {
      return instanceHandles[index];
    }

    void* getActionState(uint16_t index) {
      return &actionStateChunks[index];
    }

    void remove(uint16_t index) {
      count--;
      actionStateChunks[index] = actionStateChunks[count];
      instanceHandles[index] = instanceHandles[count];
    }
  }
}
