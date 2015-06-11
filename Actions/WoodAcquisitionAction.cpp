#include "Actions/WoodAcquisitionAction.h"

namespace Actions {
  namespace WoodAcquisitionAction {


    void build(ActionTypeDefinitionHelper *h) {
      h->setInstanceMax(32);
      h->writeSequence(2);
      NodeIndex locateNode = h->writeTreeLocalization();
    }
  }
}
