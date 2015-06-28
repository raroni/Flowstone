#ifndef WATSON_INSTANCE_LIST_H
#define WATSON_INSTANCE_LIST_H

#include "Watson/InstanceHandle.h"
#include "Watson/InstanceOrderingHandle.h"
#include "Watson/TypeIndex.h"

namespace Watson {
  namespace InstanceList {
    InstanceHandle create(TypeIndex typeIndex, InstanceOrderingHandle orderingHandle);
    TypeIndex getTypeIndex(InstanceHandle handle);
    InstanceOrderingHandle getInstanceOrderingHandle(InstanceHandle handle);
    void destroy(InstanceHandle handle);
  }
}

#endif
