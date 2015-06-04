#include "Behavior/MonsterTreeType.h"

namespace Behavior {
  namespace MonsterTreeType {
    typedef Watson::NodeIndex NI;

    NI buildWoodEnsurance(TypeDefinitionHelper *h) {
      return h->writeFailDummy();
    }

    NI buildDefense(TypeDefinitionHelper *h) {
      // todo: add actual attack/defend/whatevs
      NI defense = h->writeConcurrent(1);
      NI threatCheck = h->writeThreatCheck();
      h->setConcurrentChild(defense, 0, threatCheck);
      return defense;
    }

    NI buildHarvest(TypeDefinitionHelper *h) {
      NI harvest = h->writeLoop();
      NI sequence = h->writeSequence(2);
      NI woodEnsurance = buildWoodEnsurance(h);
      h->setSequenceChild(sequence, 0, woodEnsurance);
      // h->setSequenceChild(sequence, 1, deliverWood);
      h->setLoopChild(harvest, sequence);
      return harvest;
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
