#include "Actions3/ActionType.h"
#include "Actions3/Instance.h"
#include "Actions3/ExecutionList.h"
#include "Actions3/Action.h"
#include "Actions3/Executions.h"

namespace Actions3 {
  namespace Executions {
    namespace List = ExecutionList;

    void start(InstanceHandle instanceHandle) {
      const Request *request = Instance::getPendingRequest(instanceHandle);
      Database::EntityHandle entity = Instance::getEntityHandle(instanceHandle);

      uint8_t actionStateLength = Action::getStateLength(request->type);
      uint16_t executionIndex = List::create(instanceHandle, actionStateLength);
      void *state = List::getActionState(executionIndex);
      const void *options = request->getOptions();
      Action::startExecution(request->type, entity, state, options);
    }

    void process() {
      for(uint16_t i=0; i<List::getCount(); ++i) {
        InstanceHandle instanceHandle = List::getInstanceHandle(i);
        const Request *request = Instance::getActiveRequest(instanceHandle);
        Database::EntityHandle entity = Instance::getEntityHandle(instanceHandle);
        void *state = List::getActionState(i);
        const void *options = request->getOptions();
        Action::updateExecution(request->type, entity, state, options);
      }
    }
  }
}
