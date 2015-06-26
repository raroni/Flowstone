#include "Actions3/ActionType.h"
#include "Actions3/Instance.h"
#include "Actions3/ExecutionList.h"
#include "Actions3/Action.h"
#include "Actions3/Executions.h"

namespace Actions3 {
  namespace Executions {
    namespace List = ExecutionList;

    void start(InstanceHandle instanceHandle) {
      ActionType actionType = Instance::getRequestActionType(instanceHandle);
      Database::EntityHandle entity = Instance::getEntityHandle(instanceHandle);

      uint8_t actionStateLength = Action::getStateLength(actionType);
      uint16_t executionIndex = List::create(instanceHandle, actionStateLength);
      void *actionState = List::getActionState(executionIndex);
      Action::startExecution(actionType, entity, actionState);
    }

    void process() {
      for(uint16_t i=0; i<List::getCount(); ++i) {
        InstanceHandle instanceHandle = List::getInstanceHandle(i);
        ActionType actionType = Instance::getRequestActionType(instanceHandle);
        Database::EntityHandle entity = Instance::getEntityHandle(instanceHandle);
        void *actionState = List::getActionState(i);
        Action::updateExecution(actionType, entity, actionState);
      }
    }
  }
}
