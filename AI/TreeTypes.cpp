#include "TypeDefinitionHelper.h"
#include "Watson/TypeDefinition.h"
#include "Watson/System.h"
#include "AI/TreeTypes.h"

namespace AI {
  namespace TreeTypes {
    typedef Watson::NodeIndex NI;
    typedef Watson::TypeIndex TypeIndex;
    typedef Watson::TypeDefinition TypeDefinition;
    typedef void (*SetupFunc)(TypeDefinitionHelper *helper);

    TypeIndex monsterIndex;

    void buildMonster(TypeDefinitionHelper *h) {
      h->setInstanceMax(16);
      NI root = h->writePriority(1);
      NI threatCheck = h->writeThreatCheck();
      h->setPriorityChild(root, 0, threatCheck);
      // write me!
    }

    void build(TypeDefinition *definition, TypeIndex *index, SetupFunc setupFunc) {
      TypeDefinitionHelper helper(definition);
      setupFunc(&helper);
      *index = Watson::System::createType(definition);
      definition->reset();
    }

    void setup() {
      TypeDefinition definition;
      build(&definition, &monsterIndex, buildMonster);
    }
  }
}
