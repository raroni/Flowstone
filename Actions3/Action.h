#ifndef ACTIONS3_ACTION_H
#define ACTIONS3_ACTION_H

#include "Database/EntityHandle.h"
#include "Actions3/ActionType.h"
#include "Actions3/ActionInterface.h"

namespace Actions3 {
  namespace Action {
    void setup(ActionType type, const ActionInterface *interface);
    void startExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options);
    void updateExecution(ActionType type, Database::EntityHandle entity, void *state, const void *options);
    uint8_t getStateLength(ActionType type);
    uint8_t getOptionsLength(ActionType type);
  }
}

#endif
