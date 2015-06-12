#include "Actions/WoodAcquisitionAction.h"

namespace Actions {
  namespace WoodAcquisitionAction {
    void build(ActionTypeDefinitionHelper *h) {
      const uint8_t childCount = 2;
      h->setInstanceMax(32);
      NodeIndex sequence = h->writeSequence(childCount);
      NodeIndex children[] = {
        h->writeTreeLocalization(),
        99 // todo: fix me
      };
      h->configureSequence(sequence, childCount, children);
    }
  }
}
