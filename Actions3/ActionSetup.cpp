#include "Actions3/ActionInterface.h"
#include "Actions3/Action.h"
#include "Actions3/WoodAcquisitionAction.h"
#include "Actions3/ActionSetup.h"

namespace Actions3 {
  namespace ActionSetup {
    void setupWoodAcquisition() {
      ActionInterface interface;
      interface.startExecution = WoodAcquisitionAction::startExecution;
      Action::setup(ActionType::WoodAcquisition, &interface);
    }

    void execute() {
      setupWoodAcquisition();
    }
  }
}
