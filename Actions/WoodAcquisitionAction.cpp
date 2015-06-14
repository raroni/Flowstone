#include "Actions/WoodAcquisitionAction.h"

namespace Actions {
  namespace WoodAcquisitionAction {
    NodeIndex buildReachChop(ActionTypeDefinitionHelper *h) {
      const uint8_t childCount = 2;
      NodeIndex reachChop = h->writeConcurrent(childCount);
      NodeIndex children[] = {
        h->writeTargetReach(),
        h->writeTreeChop()
      };
      h->configureConcurrent(reachChop, childCount, children);
      return reachChop;
    }

    void build(ActionTypeDefinitionHelper *h) {
      const uint8_t childCount = 2;
      h->setInstanceMax(32);
      NodeIndex root = h->writeSequence(childCount);
      NodeIndex children[] = {
        h->writeTreeLocalization(),
        buildReachChop(h)
      };
      h->configureSequence(root, childCount, children);
    }
  }
}
