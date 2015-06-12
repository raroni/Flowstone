#include <assert.h>
#include "Actions/Node.h"
#include "Actions/NodeStructureHeader.h"
#include "Actions/ActionTypeDefinition.h"

namespace Actions {
  typedef ActionTypeDefinition ATD;

  ATD::ActionTypeDefinition() {
    reset();
  }

  NodeIndex ATD::createNode(NodeTypeIndex type, const void *args) {
    uint8_t nodeConfigLength = Node::calcConfigLength(type, args);
    uint8_t nodeStateLength = Node::calcStateLength(type, args);

    assert(nodeCount != nodeMax);
    uint8_t nodeStructureLength = sizeof(NodeStructureHeader) + nodeConfigLength;

    assert(structureCapacity >= structureLength+nodeStructureLength);

    NodeStructureHeader *header = reinterpret_cast<NodeStructureHeader*>(structure+this->structureLength);
    header->type = type;
    structureOffsets[nodeCount] = this->structureLength;
    this->structureLength += nodeStructureLength;
    stateOffsets[nodeCount] = stateLength;
    stateLength += nodeStateLength;
    return nodeCount++;
  }

  const uint8_t* ATD::getStructureOffsets() const {
    return structureOffsets;
  }

  const uint8_t* ATD::getStateOffsets() const {
    return stateOffsets;
  }

  const void* ATD::getStructure() const {
    return structure;
  }

  uint8_t ATD::getNodeCount() const {
    return nodeCount;
  }

  uint8_t ATD::getStructureLength() const {
    return structureLength;
  }

  uint8_t ATD::getStateLength() const {
    return stateLength;
  }

  void ATD::reset() {
    instanceMax = 0;
    paramLength = 0;
    structureLength = 0;
    stateLength = 0;
    nodeCount = 0;
  }
}
