#ifndef WATSON_INSTANCE_ORDERING_COLLECTION_H
#define WATSON_INSTANCE_ORDERING_COLLECTION_H

#include "Watson/TypeIndex.h"
#include "Watson/InstanceOrderingHandle.h"

namespace Watson {
  namespace InstanceOrderingCollection {
    void createList(TypeIndex typeIndex, uint16_t instanceMax);
    void create(TypeIndex typeIndex, uint16_t *index, InstanceOrderingHandle *handle);
    void destroy(TypeIndex typeIndex, InstanceOrderingHandle handle, uint16_t *sourceIndex, uint16_t *destinationIndex);
    uint16_t getIndex(TypeIndex typeIndex, InstanceOrderingHandle handle);
    uint16_t getCount(TypeIndex typeIndex);
  }
}

#endif
