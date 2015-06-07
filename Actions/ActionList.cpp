#include <assert.h>
#include "Actions/Config.h"
#include "Actions/ActionList.h"

namespace Actions {
  namespace ActionList {
    uint8_t count = 0;
    uint8_t paramLengths[Config::actionTypeMax];
    uint8_t stateLengths[Config::actionTypeMax];
    uint8_t instanceMaxes[Config::actionTypeMax];
    ActionStartFunction startFuncs[Config::actionTypeMax];

    ActionTypeIndex create(
      uint8_t paramLength,
      uint8_t instanceMax,
      uint8_t stateLength,
      ActionStartFunction startFunc
    ) {
      assert(count != Config::actionTypeMax);
      instanceMaxes[count] = instanceMax;
      stateLengths[count] = stateLength;
      paramLengths[count] = paramLength;
      startFuncs[count] = startFunc;
      return count++;
    }

    ActionStartFunction getStart(ActionTypeIndex index) {
      return startFuncs[index];
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
