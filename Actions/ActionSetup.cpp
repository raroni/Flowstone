#include "Actions/ActionInterface.h"
#include "Actions/Action.h"
#include "Actions/WoodAcquisitionAction.h"
#include "Actions/ActionSetup.h"

namespace Actions {
  namespace ActionSetup {
    void setupWoodAcquisition() {
      ActionInterface interface;
      interface.getStateLength = WoodAcquisitionAction::getStateLength;
      interface.getOptionsLength = WoodAcquisitionAction::getOptionsLength;
      interface.startExecution = WoodAcquisitionAction::startExecution;
      interface.updateExecution = WoodAcquisitionAction::updateExecution;
      interface.isExecuted = WoodAcquisitionAction::isExecuted;
      Action::setup(ActionType::WoodAcquisition, &interface);
    }

    void execute() {
      setupWoodAcquisition();
    }
  }
}
