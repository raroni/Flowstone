#include "Actions/Action.h"
#include "Actions/WoodAcquisitionAction.h"
#include "Actions/Setup.h"

namespace Actions {
  namespace Setup {
    void setupEmpty() {
      Action::setParamLength(Type::Empty, 0);
    }

    void setupWoodAcquisition() {
      Action::setParamLength(Type::WoodAcquisition, WoodAcquisitionAction::paramLength);
    }

    void run() {
      setupEmpty();
      setupWoodAcquisition();
    }
  }
}
