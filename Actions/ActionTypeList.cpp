#include <assert.h>
#include "Actions/Config.h"
#include "Actions/ActionTypeList.h"

namespace Actions {
  namespace ActionTypeList {
    uint8_t count = 0;
    uint8_t paramLengths[Config::actionTypeMax];
    uint8_t stateLengths[Config::actionTypeMax];
    uint8_t instanceMaxes[Config::actionTypeMax];
    uint8_t configBufferOffsets[Config::actionTypeMax];
    const uint16_t configBufferCapacity = 1024*50;
    uint16_t configBufferLength = 0;
    char configBuffer[configBufferCapacity];

    ActionTypeIndex create(const ActionTypeDefinition *definition) {
      assert(count != Config::actionTypeMax);
      instanceMaxes[count] = definition->instanceMax;
      stateLengths[count] = definition->stateLength;
      paramLengths[count] = definition->paramLength;
      configBufferOffsets[count] = configBufferLength;
      configBufferLength += definition->configLength;
      return count++;
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

    void* getConfig(ActionTypeIndex index) {
      uint16_t offset = configBufferOffsets[index];
      return &configBuffer[offset];
    }
  }
}
