#include "Actions/ActionTypeDefinitionHelper.h"

namespace Actions {
  typedef ActionTypeDefinitionHelper ATDH;

  ATDH::ActionTypeDefinitionHelper(ActionTypeDefinition *definition) :
  definition(definition) {

  }

  void ATDH::setInstanceMax(uint8_t max) {
    definition->instanceMax = max;
  }
}
