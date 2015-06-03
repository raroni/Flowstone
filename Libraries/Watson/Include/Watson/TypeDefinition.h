#ifndef WATSON_TREE_DEFINITION_H
#define WATSON_TREE_DEFINITION_H

#include "Watson/NodeIndex.h"

namespace Watson {
  class TypeDefinition {
  public:
    NodeIndex createNode(uint8_t type, uint8_t structureLength, uint8_t stateLength);
    void reset();
    const void* getStructure() const;
    void* getStructureNode(NodeIndex node);
    const uint16_t* getStructureOffsets() const;
    const uint16_t* getStateOffsets() const;
    uint16_t getStructureLength() const;
    uint16_t getStateLength() const;
    uint16_t getNodeCount() const;
    uint16_t instanceMax = 0;
  private:
    static const uint16_t nodeMax = 1024;
    static const uint16_t structureCapacity = 1024;
    uint16_t nodeCount = 0;
    uint16_t structureLength = 0;
    uint16_t stateLength = 0;
    char structure[structureCapacity];
    uint16_t structureOffsets[nodeMax];
    uint16_t stateOffsets[nodeMax];
  };
}

#endif
