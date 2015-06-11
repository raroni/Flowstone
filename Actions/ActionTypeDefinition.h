#ifndef ACTIONS_ACTION_TYPE_DEFINITION_H
#define ACTIONS_ACTION_TYPE_DEFINITION_H

#include <stdint.h>
#include "Actions/NodeIndex.h"
#include "Actions/NodeTypeIndex.h"

namespace Actions {
  class ActionTypeDefinition {
  public:
    ActionTypeDefinition();
    NodeIndex createNode(NodeTypeIndex type, uint8_t configLength, uint8_t stateLength);
    void reset();
    uint8_t getNodeCount() const;
    uint8_t getStructureLength() const;
    uint8_t getStateLength() const;
    uint8_t instanceMax;
    uint8_t paramLength;
    const void* getStructure() const;
    const uint8_t* getStructureOffsets() const;
    const uint8_t* getStateOffsets() const;
    void* getNodeStructure(NodeIndex index);
  private:
    uint8_t structureLength;
    uint8_t stateLength;
    uint8_t nodeCount;
    static const uint8_t nodeMax = 16;
    uint8_t structureOffsets[nodeMax];
    uint8_t stateOffsets[nodeMax];
    static const uint16_t structureCapacity = 1024;
    char structure[structureCapacity];
  };
}

#endif
