#ifndef ACTIONS_REACH_TARGET_ACTION_H
#define ACTIONS_REACH_TARGET_ACTION_H

#include "Database/EntityHandle.h"
#include "Fixie/Vector2.h"

namespace Actions {
  namespace ReachTargetAction {
    struct Options {
      Fixie::Vector2 target;
      Fixie::Num tolerance;
    };

    uint8_t getStateLength();
    uint8_t getOptionsLength();
    void startExecution(Database::EntityHandle entity, void *state, const void *options);
    void updateExecution(Database::EntityHandle entity, void *state, const void *options);
    bool isExecuted(Database::EntityHandle entity, void *state, const void *options);
  }
}

#endif
