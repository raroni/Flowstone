#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/NodeTypes.h"
#include "Actions/ActionTypes.h"
#include "Actions/ActionList.h"
#include "Actions/NodeFlow.h"
#include "Actions/Config.h"
#include "Actions/ActionStateCollection.h"
#include "Actions/ActionTypeList.h"
#include "Actions/ComponentList.h"
#include "Actions/RequestMap.h"
#include "Actions/ActionStateHandle.h"
#include "Actions/System.h"

namespace Actions {
  namespace System {
    RequestMap newRequests;
    RequestMap pendingRequests;
    ActionList activeActions;
    ActionList cancellingActions;

    void setup() {
      NodeTypes::setup();
      ActionTypes::setup();
    }

    ComponentHandle createComponent() {
      return ComponentList::create();
    }

    const Request* getRequest(ComponentHandle handle) {
      uint16_t index = ComponentList::getIndex(handle);
      return ComponentList::getRequest(index);
    }

    ActionTypeIndex createActionType(const ActionTypeDefinition *definition) {
      ActionTypeIndex index = ActionTypeList::create(definition);
      ActionStateCollection::createList(index);
      return index;
    }

    Status getStatus(ComponentHandle handle) {
      uint16_t index = ComponentList::getIndex(handle);
      return ComponentList::getStatus(index);
    }

    void startAction(ComponentHandle handle, const Request *request) {
      ActionStateHandle stateHandle = ActionStateCollection::createInstance(request->type);
      uint16_t componentIndex = ComponentList::getIndex(handle);
      ComponentList::updateStatus(componentIndex, Status::Running);
      activeActions.add(request->type, stateHandle);

      ActionStateIndex stateIndex = ActionStateCollection::getIndex(request->type, stateHandle);
      NodeFlow flow(request->type, stateIndex);
      flow.start(0);
    }

    void processNewRequests() {
      for(uint16_t i=0; i<newRequests.getCount(); ++i) {
        ComponentHandle componentHandle = newRequests.getHandle(i);
        uint16_t componentIndex = ComponentList::getIndex(componentHandle);
        const Request *request = newRequests.getRequest(i);
        ComponentList::updateRequest(componentIndex, request);
        Status status = ComponentList::getStatus(componentHandle);
        if(status == Status::Running) {
          // cannot yet handle
          // pendingRequests.doSomething();
          assert(false);
        }
        else if(
          status == Status::Initialized ||
          status == Status::Completed ||
          status == Status::Cancelled
        ) {
          startAction(componentHandle, request);
          pendingRequests.unset(componentHandle);
        }
      }
      newRequests.clear();
    }

    void processCancellingActions() {

    }

    void processActiveActions() {
      NodeFlow flow;
      for(uint16_t i=0; i<activeActions.getCount(); ++i) {
        ActionTypeIndex type = activeActions.getType(i);
        ActionStateHandle actionStateHandle = activeActions.getState(i);
        ActionStateIndex actionStateIndex = ActionStateCollection::getIndex(type, actionStateHandle);
        flow.configure(type, actionStateIndex);
        if(flow.isCompleted(0)) {
          activeActions.remove(i);
          i--;
        }
      }
    }

    void processPendingRequests() {

    }

    void update() {
      processCancellingActions();
      processActiveActions();
      processNewRequests();
      processPendingRequests();
    }

    void request(ComponentHandle handle, const Request *request) {
      newRequests.set(handle, request);
    }
  }
}
