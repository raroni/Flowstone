#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "Actions/Type.h"

namespace Actions {
  namespace Action {
    void setParamLength(Type type, uint8_t length);
    uint8_t getParamLength(Type type);
  }
}

#endif
