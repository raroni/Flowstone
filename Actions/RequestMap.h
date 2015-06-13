#ifndef ACTIONS_REQUEST_MAP_H
#define ACTIONS_REQUEST_MAP_H

#include "Actions/ComponentHandle.h"
#include "Actions/Request.h"

namespace Actions {
  class RequestMap {
  public:
    uint16_t getCount() const;
    void set(ComponentHandle handle, const Request *request);
    void unset(ComponentHandle handle);
    void clear();
    ComponentHandle getHandle(uint8_t index) const;
    const Request* getRequest(uint8_t index) const;
  private:
    // BREADCRUMB: UNSET() og SET() kan begge bruge denne:
    bool findIndex(ComponentHandle handle, uint8_t *index) const;
    static const uint8_t max = 128;
    ComponentHandle handles[max];
    Request requests[max];
    uint8_t count = 0;
  };
}

#endif
