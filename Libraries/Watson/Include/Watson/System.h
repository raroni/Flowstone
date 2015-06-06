#ifndef WATSON_SYSTEM_H
#define WATSON_SYSTEM_H

#include "Watson/InstanceOrderingHandle.h"
#include "Watson/InstanceHandle.h"
#include "Watson/Stream.h"
#include "Watson/TypeDefinition.h"
#include "Watson/Board.h"
#include "Watson/TypeIndex.h"

namespace Watson {
  namespace System {
    void initialize();
    TypeIndex createType(const TypeDefinition *definition);
    InstanceHandle createInstance(TypeIndex typeIndex);
    uint16_t getInstanceCount(TypeIndex typeIndex);
    void destroyTree(InstanceHandle treeHandle);
    Board* getBoardByHandle(InstanceHandle treeHandle);
    Board* getBoardByIndices(TypeIndex typeIndex, uint16_t instanceIndex);
    Stream* getActionStream(TypeIndex typeIndex, uint16_t instanceIndex);
    uint8_t getTypeCount();
    void update();
    void clearActionStreams();
  }
}

#endif
