#include <assert.h>
#include "Actions/RequestList.h"

namespace Actions {
  void RequestList::add(ComponentHandle handle, const Request *request) {
    assert(count != capacity);
    handles[count] = handle;
    requests[count] = *request;
    count++;
  }

  const Request* RequestList::getRequest(uint8_t index) const {
    return &requests[index];
  }

  ComponentHandle RequestList::getHandle(uint8_t index) const {
    return handles[index];
  }

  void RequestList::clear() {
    count = 0;
  }

  uint8_t RequestList::getCount() const {
    return count;
  }
}
