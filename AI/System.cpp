#include <assert.h>
#include "Misc/HandleList.h"
#include "AI/System.h"

namespace AI {
  namespace System {
    const static uint16_t max = 256;
    uint16_t indices[max];
    Handle handles[max];
    HandleList handleList(max, indices, handles);

    void initialize() {
      // setup nodes
    }

    Handle create(Type type) {
      assert(handleList.getCount() != max);
      uint16_t index;
      Handle handle;
      handleList.create(&index, &handle);
      return handle;
    }

    void update() {

    }
  }
}
