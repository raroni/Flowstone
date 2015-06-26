#include <assert.h>
#include "Actions3/ExecutionList.h"

namespace Actions3 {
  namespace ExecutionList {
    const uint8_t actionStateLengthMax = 4;
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
      instanceHandles[count];
      return count++;
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
