#ifndef ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H
#define ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H

#include "ActionTypeDefinition.h"

namespace Actions {
  class ActionTypeDefinitionHelper {
  public:
    ActionTypeDefinitionHelper(ActionTypeDefinition *definition);
    void setInstanceMax(uint8_t max);
  private:
    ActionTypeDefinition *definition = nullptr;
  };
}

#endif
