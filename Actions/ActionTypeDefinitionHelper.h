#ifndef ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H
#define ACTIONS_ACTION_TYPE_DEFINITION_HELPER_H

#include "Actions/NodeIndex.h"
#include "ActionTypeDefinition.h"
#include "Actions/ActionTypeIndex.h"

namespace Actions {
  class ActionTypeDefinitionHelper {
  public:
    ActionTypeDefinitionHelper(ActionTypeDefinition *definition);
    void setInstanceMax(uint8_t max);
    NodeIndex writeSequence(uint8_t childCount);
    NodeIndex writeTreeLocalization();
  private:
    ActionTypeDefinition *definition = nullptr;
  };
}

#endif
