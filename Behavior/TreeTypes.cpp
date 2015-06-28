#include "Watson/TypeDefinition.h"
#include "Watson/System.h"
#include "Behavior/TypeDefinitionHelper.h"
#include "Behavior/WorkerTreeType.h"
#include "Behavior/TreeTypes.h"

namespace Behavior {
  namespace TreeTypes {
    typedef Watson::TypeIndex TypeIndex;
    typedef Watson::TypeDefinition TypeDefinition;
    typedef void (*SetupFunc)(TypeDefinitionHelper *helper);

    TypeIndex workerIndex;

    void build(TypeDefinition *definition, TypeIndex *index, SetupFunc setupFunc) {
      TypeDefinitionHelper helper(definition);
      setupFunc(&helper);
      *index = Watson::System::createType(definition);
      definition->reset();
    }

    void setup() {
      TypeDefinition definition;
      build(&definition, &workerIndex, WorkerTreeType::build);
    }
  }
}
