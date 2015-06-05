#ifndef WATSON_SYSTEM_H
#define WATSON_SYSTEM_H

#include "Watson/InstanceOrderingHandle.h"
#include "Watson/InstanceHandle.h"
#include "Watson/TypeDefinition.h"
#include "Watson/Board.h"
#include "Watson/TypeIndex.h"

namespace Watson {
  namespace System {
    void initialize();
    TypeIndex createType(const TypeDefinition *definition);
    InstanceHandle createInstance(TypeIndex typeIndex);
    void destroyTree(InstanceHandle treeHandle);
    Board* getBoard(InstanceHandle treeHandle);
    void update();
    void clearActionStreams();
  }
}

#endif
