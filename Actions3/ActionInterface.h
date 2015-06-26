#ifndef ACTIONS3_ACTION_INTERFACE_H
#define ACTIONS3_ACTION_INTERFACE_H

#include "Database/EntityHandle.h"

namespace Actions3 {
  struct ActionInterface {
    void (*startExecution)(Database::EntityHandle entity) = nullptr;
  };
}

#endif
