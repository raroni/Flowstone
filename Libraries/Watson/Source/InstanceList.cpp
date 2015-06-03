#include "Misc/IntegerPool.h"
#include "Watson/Config.h"
#include "Watson/InstanceList.h"

namespace Watson {
  namespace InstanceList {
    const uint16_t max = Config::instanceMax;
    TypeIndex typeIndices[max];
    InstanceOrderingHandle orderingHandles[max];
    IntegerPool pool;

    InstanceHandle create(TypeIndex typeIndex, InstanceOrderingHandle orderingHandle) {
      InstanceHandle handle = pool.obtain();
      typeIndices[handle] = typeIndex;
      orderingHandles[handle] = orderingHandle;
      return handle;
    }

    TypeIndex getTypeIndex(InstanceHandle handle) {
      return typeIndices[handle];
    }

    InstanceOrderingHandle getInstanceOrderingHandle(InstanceHandle handle) {
      return orderingHandles[handle];
    }

    void destroy(InstanceOrderingHandle handle) {
      pool.release(handle);
    }
  }
}
