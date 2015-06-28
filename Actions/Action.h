#ifndef ACTIONS_ACTION_H
#define ACTIONS_ACTION_H

#include "Database/EntityHandle.h"
#include "Actions/ActionType.h"
#include "Actions/ActionInterface.h"

namespace Actions {
  namespace Action {
    void setup(ActionType type, const ActionInterface *interface);
    void startExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options);
    void updateExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options);
    bool isExecuted(ActionType type, Database::EntityHandle entity, void *state, const void *options);
    uint8_t getStateLength(ActionType type);
    uint8_t getOptionsLength(ActionType type);
  }
}

#endif
