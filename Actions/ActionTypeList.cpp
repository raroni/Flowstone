#include <string.h>
#include <assert.h>
#include "Actions/Config.h"
#include "Actions/ActionTypeList.h"

namespace Actions {
  namespace ActionTypeList {
    uint8_t count = 0;
    uint16_t nodeCount = 0;
    uint8_t paramLengths[Config::actionTypeMax];
    uint8_t stateLengths[Config::actionTypeMax];
    uint8_t instanceMaxes[Config::actionTypeMax];
    uint16_t nodeOffsets[Config::actionTypeMax];
    uint8_t nodeCounts[Config::actionTypeMax];
    uint16_t structureBufferOffsets[Config::actionTypeMax];

    const uint16_t structureBufferCapacity = 1024*10;
    char structureBuffer[structureBufferCapacity];
    uint16_t structureBufferLength = 0;

    const uint16_t structureOffsetCapacity = 1024;
    uint8_t structureOffsetBuffer[structureOffsetCapacity];

    const uint16_t stateOffsetCapacity = 1024;
    uint8_t stateOffsetBuffer[stateOffsetCapacity];

    ActionTypeIndex create(const ActionTypeDefinition *definition) {
      assert(count != Config::actionTypeMax);
      assert(definition->instanceMax != 0);
      assert(structureBufferCapacity >= structureBufferLength + definition->getStructureLength());
      assert(structureOffsetCapacity >= nodeCount + definition->getNodeCount());
      assert(stateOffsetCapacity >= nodeCount + definition->getNodeCount());

      paramLengths[count] = definition->paramLength;
      stateLengths[count] = definition->getStateLength();
      instanceMaxes[count] = definition->instanceMax;
      nodeOffsets[count] = nodeCount;
      nodeCounts[count] = definition->getNodeCount();
      structureBufferOffsets[count] = structureBufferLength;

      memcpy(
        structureBuffer+structureBufferLength,
        definition->getStructure(),
        definition->getStructureLength()
      );
      memcpy(
        structureOffsetBuffer+nodeCount,
        definition->getStructureOffsets(),
        definition->getNodeCount()*sizeof(uint8_t)
      );
      memcpy(
        stateOffsetBuffer+nodeCount,
        definition->getStateOffsets(),
        definition->getNodeCount()*sizeof(uint8_t)
      );

      nodeCount += definition->getNodeCount();
      structureBufferLength += definition->getStructureLength();
      return count++;
    }

    void* getNodeStructure(ActionTypeIndex typeIndex, NodeIndex nodeIndex) {
      uint16_t nodeOffset = nodeOffsets[typeIndex];

      uint16_t structureTypeOffset = structureBufferOffsets[typeIndex];
      uint16_t structureNodeOffset = structureOffsetBuffer[nodeOffset+nodeIndex];
      uint16_t structureOffset = structureTypeOffset + structureNodeOffset;
      return structureBuffer+structureOffset;
    }

    uint16_t getNodeStateOffset(ActionTypeIndex typeIndex, NodeIndex nodeIndex) {
      uint16_t typeOffset = nodeOffsets[typeIndex];
      return stateOffsetBuffer[typeOffset+nodeIndex];
    }

    uint8_t getStateLength(ActionTypeIndex index) {
      return stateLengths[index];
    }

    uint8_t getParamLength(ActionTypeIndex index) {
      return paramLengths[index];
    }

    uint8_t getInstanceMax(ActionTypeIndex index) {
      return instanceMaxes[index];
    }
  }
}
