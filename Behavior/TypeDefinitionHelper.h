#ifndef BEHAVIOR_TREE_DEFINITION_HELPER_H
#define BEHAVIOR_TREE_DEFINITION_HELPER_H

#include "Watson/TypeDefinition.h"
#include "Watson/NodeIndex.h"
#include "Watson/NodeType.h"
#include "NodeType.h"

namespace Behavior {
  class TypeDefinitionHelper {
  public:
    TypeDefinitionHelper(Watson::TypeDefinition *definition);
    Watson::NodeIndex writePriority(uint8_t childCount);
    Watson::NodeIndex writeConcurrent(uint8_t childCount);
    Watson::NodeIndex writeThreatCheck();
    Watson::NodeIndex writeFailDummy();
    Watson::NodeIndex writeRunDummy();
    void setPriorityChild(Watson::NodeIndex priorityIndex, uint8_t childSlot, Watson::NodeIndex childIndex);
    void setConcurrentChild(Watson::NodeIndex concurrentIndex, uint8_t childSlot, Watson::NodeIndex childIndex);
    void setInstanceMax(uint16_t max);
  private:
    struct Creation {
      Watson::NodeIndex index;
      void *structureNode;
    };
    Watson::TypeDefinition *definition = nullptr;
    void* getStructureNode(Watson::NodeIndex index);
    Creation create(uint8_t type, uint16_t structureLength, uint16_t stateLength);
    Creation createWatson(Watson::NodeType type, uint16_t structureLength, uint16_t stateLength);
    Creation createCustom(NodeType type, uint16_t structureLength, uint16_t stateLength);
  };
}

#endif
