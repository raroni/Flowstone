#ifndef ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H
#define ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H

#include "ActionTypeDefinition.h"

namespace Actions {
  class ActionTypeDefinitionHelper {
  public:
    ActionTypeDefinitionHelper(ActionTypeDefinition *definition);
  private:
    ActionTypeDefinition *definition = nullptr;
  };
}

#endif
