#include <assert.h>
#include "Misc/HandleList.h"
#include "Actions/Setup.h"
#include "Actions/Config.h"
#include "Actions/RequestMap.h"
#include "Actions/System.h"

namespace Actions {
  namespace System {
    const uint16_t max = Config::actionMax;
    uint16_t indices[max];
    Handle handles[max];
    HandleList handleList(max, indices, handles);
    Status statuses[max];
    Type types[max];
    RequestParamSet requestParams[max];
    RequestMap pendingRequests;

    void setup() {
      Setup::run();
    }

    Handle create() {
      assert(handleList.getCount() != max);
      uint16_t index;
      Handle handle;
      handleList.create(&index, &handle);
      types[index] = Type::Empty;
      return handle;
    }

    Request getRequest(Handle handle) {
      uint16_t index = handleList.getIndex(handle);
      Request request;
      request.type = types[index];
      RequestParamSet *set = &requestParams[index];
      request.setParams(set->getData());
      return request;
    }

    Status getStatus(Handle handle) {
      uint16_t index = handleList.getIndex(handle);
      return statuses[index];
    }

    void updateActions() {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        // update action
      }
    }

    void checkPending() {
      for(uint16_t i=0; i<pendingRequests.getCount(); ++i) {
        // is action is completed, start new
      }
    }

    void update() {
      updateActions();
      checkPending();
    }

    void request(Handle handle, const Request *request) {
      pendingRequests.set(handle, request);
    }
  }
}
