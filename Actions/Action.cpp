#include <assert.h>
#include "Actions/Config.h"
#include "Actions/Action.h"

namespace Actions {
  namespace Action {
    uint8_t paramLengths[Config::actionMax] = { UINT8_MAX };

    void setParamLength(Type type, uint8_t length) {
      paramLengths[static_cast<uint8_t>(type)] = length;
    }

    uint8_t getParamLength(Type type) {
      uint8_t length = paramLengths[static_cast<uint8_t>(type)];
      assert(length != UINT8_MAX);
      return length;
    }
  }
}
