#ifndef ACTIONS3_WOOD_ACQUISITION_ACTION_H
#define ACTIONS3_WOOD_ACQUISITION_ACTION_H

#include "Database/EntityHandle.h"

namespace Actions3 {
  namespace WoodAcquisitionAction {
    uint8_t getStateLength();
    uint8_t getOptionsLength();
    void startExecution(Database::EntityHandle entity, void *state, const void *options);
    void updateExecution(Database::EntityHandle entity, void *state, const void *options);
    bool isExecuted(Database::EntityHandle entity, void *state, const void *options);
  }
}

#endif
