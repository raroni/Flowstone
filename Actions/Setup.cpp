#include "Actions/ActionTypeList.h"
#include "Actions/StateCollection.h"
#include "Actions/EmptyAction.h"
#include "Actions/WoodAcquisitionAction.h"
#include "Actions/ActionTypes.h"
#include "Actions/Setup.h"

namespace Actions {
  namespace Setup {
    void setupEmpty() {
      ActionTypeIndex index = ActionTypeList::create(
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
      ActionTypeIndex index = ActionTypeList::create(
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
