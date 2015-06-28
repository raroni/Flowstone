#include <assert.h>
#include <string.h>
#include "Watson/Config.h"
#include "Watson/TypeList.h"

namespace Watson {
  namespace TypeList {
    uint8_t count = 0;
    const uint16_t structureBufferCapacity = 1024*10;
    char structureBuffer[structureBufferCapacity];
    uint16_t structureBufferLength = 0;

    const uint16_t structureOffsetCapacity = 1024;
    uint16_t structureOffsetBuffer[structureOffsetCapacity];
    uint16_t structureOffsetBufferLength = 0;

    const uint16_t stateOffsetCapacity = 1024;
    uint16_t stateOffsetBuffer[stateOffsetCapacity];
    uint16_t stateOffsetBufferLength = 0;

    uint16_t instanceMaxes[Config::typeMax];
    uint16_t stateLengths[Config::typeMax];
    uint16_t nodeCounts[Config::typeMax];
    uint16_t structureOffsetBufferOffsets[Config::typeMax];

    TypeIndex create(const TypeDefinition *definition) {
      assert(structureBufferCapacity >= structureBufferLength + definition->getStructureLength());
      assert(structureOffsetCapacity >= structureOffsetBufferLength + definition->getNodeCount());
      assert(stateOffsetCapacity >= stateOffsetBufferLength + definition->getNodeCount());

      uint16_t nodeCount = definition->getNodeCount();

      memcpy(
        structureBuffer+structureBufferLength,
        definition->getStructure(),
        definition->getStructureLength()
      );
      memcpy(
        structureOffsetBuffer+structureOffsetBufferLength,
        definition->getStructureOffsets(),
        nodeCount*sizeof(uint16_t)
      );
      memcpy(
        stateOffsetBuffer+stateOffsetBufferLength,
        definition->getStateOffsets(),
        nodeCount*sizeof(uint16_t)
      );
      instanceMaxes[count] = definition->instanceMax;
      stateLengths[count] = definition->getStateLength();
      nodeCounts[count] = nodeCount;
      structureOffsetBufferOffsets[count] = structureOffsetBufferLength;

      structureBufferLength += definition->getStructureLength();
      structureOffsetBufferLength += nodeCount;
      stateOffsetBufferLength += nodeCount;
      return count++;
    }

    uint8_t getCount() {
      return count;
    }

    uint16_t getNodeCount(TypeIndex typeIndex) {
      return nodeCounts[typeIndex];
    }

    uint16_t getInstanceMax(TypeIndex typeIndex) {
      return instanceMaxes[typeIndex];
    }

    uint16_t getStateLength(TypeIndex typeIndex) {
      return stateLengths[typeIndex];
    }

    void* getStructureNode(TypeIndex typeIndex, NodeIndex nodeIndex) {
      uint16_t typeOffset = structureOffsetBufferOffsets[typeIndex];
      uint16_t nodeOffset = structureOffsetBuffer[typeOffset+nodeIndex];
      return structureBuffer+nodeOffset;
    }
  }
}
