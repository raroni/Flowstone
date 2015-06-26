#ifndef ACTIONS3_WOOD_ACQUISITION_ACTION_H
#define ACTIONS3_WOOD_ACQUISITION_ACTION_H

#include "Database/EntityHandle.h"

namespace Actions3 {
  namespace WoodAcquisitionAction {
    uint8_t getStateLength();
    void startExecution(Database::EntityHandle, void *state);
  }
}

#endif
