#ifndef ACTIONS_REQUEST_LIST_H
#define ACTIONS_REQUEST_LIST_H

#include "Actions/Request.h"
#include "Actions/ComponentHandle.h"

namespace Actions {
  class RequestList {
  public:
    void add(ComponentHandle handle, const Request* request);
    const Request* getRequest(uint8_t index) const;
    ComponentHandle getHandle(uint8_t index) const;
    uint8_t getCount() const;
    void clear();
  private:
    static const uint8_t capacity = 128;
    Request requests[capacity];
    ComponentHandle handles[capacity];
    uint8_t count = 0;
  };
}

#endif
