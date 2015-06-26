#include "Actions3/ActionType.h"
#include "Actions3/Instance.h"
#include "Actions3/ExecutionList.h"
#include "Actions3/Action.h"
#include "Actions3/Executions.h"

namespace Actions3 {
  namespace Executions {
    namespace List = ExecutionList;

    void start(InstanceHandle handle) {
      ActionType actionType = Instance::getRequestActionType(handle);
      Database::EntityHandle entity = Instance::getEntityHandle(handle);
      Action::startExecution(actionType, entity);
      List::create(handle);
    }

    void process() {

    }
  }
}
