#ifndef ACTIONS_REQUEST_MAP_H
#define ACTIONS_REQUEST_MAP_H

#include "Actions/Request.h"
#include "Actions/InstanceHandle.h"

namespace Actions {
  class RequestMap {
  public:
    uint16_t getCount() const;
    void set(InstanceHandle handle, const Request *request);
    void unset(InstanceHandle handle);
    void clear();
    InstanceHandle getHandle(uint8_t index) const;
    const Request* getRequest(uint8_t index) const;
    void remove(uint8_t index);
  private:
    bool findIndex(InstanceHandle handle, uint8_t *index) const;
    static const uint8_t max = 128;
    InstanceHandle handles[max];
    Request requests[max];
    uint8_t count = 0;
  };
}

#endif
