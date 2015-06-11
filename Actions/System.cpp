#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/NodeTypes.h"
#include "Actions/ActionTypes.h"
#include "Actions/Config.h"
#include "Actions/ActionStateCollection.h"
#include "Actions/ActionTypeList.h"
#include "Actions/ComponentList.h"
#include "Actions/RequestMap.h"
#include "Actions/RequestList.h"
#include "Actions/ActionStateHandle.h"
#include "Actions/System.h"

namespace Actions {
  namespace System {
    RequestList newRequests;
    RequestMap pendingRequests;

    void setup() {
      NodeTypes::setup();
      ActionTypes::setup();
    }

    ComponentHandle createComponent() {
      return ComponentList::create();
    }

    const Request* getActiveRequest(ComponentHandle handle) {
      uint16_t index = ComponentList::getIndex(handle);
      return ComponentList::getActiveRequest(index);
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
      ComponentList::updateActiveRequest(componentIndex, request);
      ComponentList::updateStateHandle(componentIndex, stateHandle);
      ComponentList::updateStatus(componentIndex, Status::Running);
      ActionStateIndex stateIndex = ActionStateCollection::getIndex(request->type, stateHandle);
      void *state = ActionStateCollection::get(request->type, stateIndex);
      // todo: fix this
      // ActionTypeList::getStart(request->type)(state);
    }

    void processNewRequests() {
      for(uint16_t i=0; i<newRequests.getCount(); ++i) {
        ComponentHandle componentHandle = newRequests.getHandle(i);
        Status status = ComponentList::getStatus(componentHandle);
        if(status == Status::Running) {
          // cannot yet handle
          // pendingRequests.doSomething();
          assert(false);
        }
        else {
          const Request *request = newRequests.getRequest(i);
          startAction(componentHandle, request);
        }
      }
      newRequests.clear();
    }

    void processStoppingActions() {

    }

    void processActiveActions() {

    }

    void update() {
      processNewRequests();
      processStoppingActions();
      processActiveActions();
    }

    void request(ComponentHandle handle, const Request *request) {
      newRequests.add(handle, request);
    }
  }
}
