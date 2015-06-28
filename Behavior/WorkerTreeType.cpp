#include "Behavior/WorkerTreeType.h"

namespace Behavior {
  namespace WorkerTreeType {
    typedef Watson::NodeIndex NI;

    NI buildInverseWoodCheck(TypeDefinitionHelper *h) {
      NI inverseWoodCheck = h->writeInverter();
      NI woodCheck = h->writeWoodCheck();
      h->setInverterChild(inverseWoodCheck, woodCheck);
      return inverseWoodCheck;
    }

    NI buildWoodEnsurance(TypeDefinitionHelper *h) {
      NI woodEnsurance = h->writeSequence(2);
      NI inverseWoodCheck = buildInverseWoodCheck(h);
      NI woodAcquisition = h->writeWoodAcquisition();
      h->setSequenceChild(woodEnsurance, 0, inverseWoodCheck);
      h->setSequenceChild(woodEnsurance, 1, woodAcquisition);
      return woodEnsurance;
    }

    NI buildWoodDelivery(TypeDefinitionHelper *h) {
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
      NI harvest = h->writeSequence(2);
      NI woodEnsurance = buildWoodEnsurance(h);
      NI woodDelivery = buildWoodDelivery(h);
      h->setSequenceChild(harvest, 0, woodEnsurance);
      h->setSequenceChild(harvest, 1, woodDelivery);
      return harvest;
    }

    NI buildHarvestLoop(TypeDefinitionHelper *h) {
      NI harvestLoop = h->writeLoop();
      NI harvest = buildHarvest(h);
      h->setLoopChild(harvestLoop, harvest);
      return harvestLoop;
    }

    NI buildIdle(TypeDefinitionHelper *h) {
      return h->writeRunDummy();
    }

    void build(TypeDefinitionHelper *h) {
      h->setInstanceMax(16);

      NI root = h->writePriority(3);
      NI defense = buildDefense(h);
      NI harvestLoop = buildHarvestLoop(h);
      NI idle = buildIdle(h);
      h->setPriorityChild(root, 0, defense);
      h->setPriorityChild(root, 1, harvestLoop);
      h->setPriorityChild(root, 2, idle);
    }
  }
}
