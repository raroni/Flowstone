#ifndef WATSON_TYPE_LIST_H
#define WATSON_TYPE_LIST_H

#include "Watson/TypeIndex.h"
#include "Watson/TypeDefinition.h"

namespace Watson {
  namespace TypeList {
    TypeIndex create(const TypeDefinition *definition);
    uint8_t getCount();
    uint16_t getNodeCount(TypeIndex typeIndex);
    uint16_t getInstanceMax(TypeIndex typeIndex);
    uint16_t getStateLength(TypeIndex typeIndex);
    void* getStructureNode(TypeIndex typeIndex, NodeIndex nodeIndex);
  }
}

#endif
