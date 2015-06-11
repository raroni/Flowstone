#include "Actions/ActionTypeDefinition.h"

namespace Actions {
  ActionTypeDefinition::ActionTypeDefinition() {
    reset();
  }

  void ActionTypeDefinition::reset() {
    instanceMax = 0;
    paramLength = 0;
    configLength = 0;
    stateLength = 0;
  }
}
