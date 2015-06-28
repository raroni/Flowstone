#include "Watson/TypeDefinition.h"
#include "Watson/System.h"
#include "Behavior/TypeDefinitionHelper.h"
#include "Behavior/MonsterTreeType.h"
#include "Behavior/TreeTypes.h"

namespace Behavior {
  namespace TreeTypes {
    typedef Watson::TypeIndex TypeIndex;
    typedef Watson::TypeDefinition TypeDefinition;
    typedef void (*SetupFunc)(TypeDefinitionHelper *helper);

    TypeIndex monsterIndex;

    void build(TypeDefinition *definition, TypeIndex *index, SetupFunc setupFunc) {
      TypeDefinitionHelper helper(definition);
      setupFunc(&helper);
      *index = Watson::System::createType(definition);
      definition->reset();
    }

    void setup() {
      TypeDefinition definition;
      build(&definition, &monsterIndex, MonsterTreeType::build);
    }
  }
}
