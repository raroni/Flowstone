#include "Actions/ActionList.h"
#include "Actions/StateCollection.h"
#include "Actions/EmptyAction.h"
#include "Actions/WoodAcquisitionAction.h"
#include "Actions/ActionTypes.h"
#include "Actions/Setup.h"

namespace Actions {
  namespace Setup {
    void setupEmpty() {
      ActionTypeIndex index = ActionList::create(
        EmptyAction::instanceMax,
        EmptyAction::configLength,
        EmptyAction::stateLength,
        EmptyAction::paramLength,
        EmptyAction::start
      );
      StateCollection::createList(index);
      ActionTypes::empty = index;
    }

    void setupWoodAcquisition() {
      ActionTypeIndex index = ActionList::create(
        WoodAcquisitionAction::instanceMax,
        WoodAcquisitionAction::configLength,
        WoodAcquisitionAction::stateLength,
        WoodAcquisitionAction::paramLength,
        WoodAcquisitionAction::start
      );
      StateCollection::createList(index);
      ActionTypes::woodAcquisition = index;
    }

    void run() {
      setupEmpty();
      setupWoodAcquisition();
    }
  }
}
