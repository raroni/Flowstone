#include <assert.h>
#include "Misc/HandleList.h"
#include "Watson/Config.h"
#include "Watson/InstanceOrderingCollection.h"

namespace Watson {
  HandleList handleLists[Config::typeMax];

  const uint16_t pairCapacity = 1024;
  uint16_t indexBuffer[pairCapacity];
  InstanceOrderingHandle handleBuffer[pairCapacity];
  uint16_t pairLength = 0;

  namespace InstanceOrderingCollection {
    void createList(TypeIndex typeIndex, uint16_t instanceMax) {
      assert(pairCapacity >= pairLength+instanceMax);

      handleLists[typeIndex].configure(
        instanceMax,
        indexBuffer+pairLength,
        handleBuffer+pairLength
      );
      pairLength += instanceMax;
    }

    uint16_t getIndex(TypeIndex typeIndex, InstanceOrderingHandle handle) {
      return handleLists[typeIndex].getIndex(handle);
    }

    void destroy(TypeIndex typeIndex, InstanceOrderingHandle handle, uint16_t *sourceIndex, uint16_t *destinationIndex) {
      handleLists[typeIndex].destroy(handle, sourceIndex, destinationIndex);
    }

    void create(TypeIndex typeIndex, uint16_t *index, InstanceOrderingHandle *handle) {
      handleLists[typeIndex].create(index, handle);
    }

    uint16_t getCount(TypeIndex typeIndex) {
      return handleLists[typeIndex].getCount();
    }
  }
}
