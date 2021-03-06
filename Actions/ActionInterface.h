#ifndef ACTIONS_ACTION_INTERFACE_H
#define ACTIONS_ACTION_INTERFACE_H

#include "Database/EntityHandle.h"

namespace Actions {
  struct ActionInterface {
    uint8_t (*getStateLength)() = nullptr;
    uint8_t (*getOptionsLength)() = nullptr;
    void (*startExecution)(Database::EntityHandle entity, void *state, const void *options) = nullptr;
    bool (*isExecuted)(Database::EntityHandle entity, void *state, const void *options) = nullptr;
    void (*updateExecution)(Database::EntityHandle entity, void *state, const void *options) = nullptr;
  };
}

#endif
