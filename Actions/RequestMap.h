#ifndef ACTIONS_REQUEST_MAP_H
#define ACTIONS_REQUEST_MAP_H

#include "Actions/ComponentHandle.h"
#include "Actions/Request.h"

namespace Actions {
  class RequestMap {
  public:
    uint16_t getCount() const;
    void set(ComponentHandle handle, const Request *request);
  private:
    uint16_t count = 0;
  };
}

#endif
