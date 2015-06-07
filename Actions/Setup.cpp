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
        EmptyAction::paramLength,
        EmptyAction::instanceMax,
        EmptyAction::stateLength,
        EmptyAction::start
      );
      StateCollection::createList(index);
      ActionTypes::empty = index;
    }

    void setupWoodAcquisition() {
      ActionTypeIndex index = ActionList::create(
        WoodAcquisitionAction::paramLength,
        WoodAcquisitionAction::instanceMax,
        WoodAcquisitionAction::stateLength,
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
