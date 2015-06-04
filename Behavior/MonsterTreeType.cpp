#include "Behavior/MonsterTreeType.h"

namespace Behavior {
  namespace MonsterTreeType {
    typedef Watson::NodeIndex NI;

    NI buildDefense(TypeDefinitionHelper *h) {
      // todo: add actual attack/defend/whatevs
      NI defense = h->writeConcurrent(1);
      NI threatCheck = h->writeThreatCheck();
      h->setConcurrentChild(defense, 0, threatCheck);
      return defense;
    }

    NI buildHarvest(TypeDefinitionHelper *h) {
      return h->writeFailDummy();
    }

    NI buildIdle(TypeDefinitionHelper *h) {
      return h->writeRunDummy();
    }

    void build(TypeDefinitionHelper *h) {
      h->setInstanceMax(16);

      NI root = h->writePriority(3);
      NI defense = buildDefense(h);
      NI harvest = buildHarvest(h);
      NI idle = buildIdle(h);
      h->setPriorityChild(root, 0, defense);
      h->setPriorityChild(root, 1, harvest);
      h->setPriorityChild(root, 2, idle);
    }
  }
}
