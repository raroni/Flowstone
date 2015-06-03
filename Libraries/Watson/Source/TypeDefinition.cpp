#include "Watson/TypeDefinition.h"

namespace Watson {
  NodeIndex TypeDefinition::createNode(uint8_t type, uint8_t structureLength, uint8_t stateLength) {
    *reinterpret_cast<uint8_t*>(structure+this->structureLength) = type;
    structureOffsets[nodeCount] = this->structureLength;
    this->structureLength += structureLength;
    stateOffsets[nodeCount] = stateLength;
    stateLength += stateLength;
    return nodeCount++;
  }

  const void* TypeDefinition::getStructure() const {
    return structure;
  }

  void* TypeDefinition::getStructureNode(NodeIndex index) {
    return structure + structureOffsets[index];
  }

  const uint16_t* TypeDefinition::getStructureOffsets() const {
    return structureOffsets;
  }

  const uint16_t* TypeDefinition::getStateOffsets() const {
    return stateOffsets;
  }

  uint16_t TypeDefinition::getNodeCount() const {
    return nodeCount;
  }

  uint16_t TypeDefinition::getStructureLength() const {
    return structureLength;
  }

  uint16_t TypeDefinition::getStateLength() const {
    return stateLength;
  }

  void TypeDefinition::reset() {
    nodeCount = 0;
    structureLength = 0;
    stateLength = 0;
  }
}
