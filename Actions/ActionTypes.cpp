#include "Actions/EmptyAction.h"
#include "Actions/WoodAcquisitionAction.h"
#include "Actions/ActionTypeDefinition.h"
#include "Actions/System.h"
#include "Actions/ActionTypeDefinitionHelper.h"
#include "Actions/ActionTypes.h"

namespace Actions {
  namespace ActionTypes {
    ActionTypeIndex empty;
    ActionTypeIndex woodAcquisition;

    typedef void (*BuildFunc)(ActionTypeDefinitionHelper *helper);

    void build(ActionTypeDefinition *definition, ActionTypeIndex *index, BuildFunc buildFunc) {
      ActionTypeDefinitionHelper helper(definition);
      buildFunc(&helper);
      *index = System::createActionType(definition);
      definition->reset();
    }

    void setup() {
      ActionTypeDefinition definition;
      build(&definition, &empty, EmptyAction::build);
      build(&definition, &woodAcquisition, WoodAcquisitionAction::build);
    }
  }
}
