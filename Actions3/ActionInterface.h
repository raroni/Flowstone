#ifndef ACTIONS3_ACTION_INTERFACE_H
#define ACTIONS3_ACTION_INTERFACE_H

#include "Database/EntityHandle.h"

namespace Actions3 {
  struct ActionInterface {
    uint8_t (*getStateLength)() = nullptr;
    void (*startExecution)(Database::EntityHandle entity, void *state) = nullptr;
  };
}

#endif
