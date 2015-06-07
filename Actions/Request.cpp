#include <assert.h>
#include "Actions/ActionList.h"
#include "Actions/Request.h"

namespace Actions {
  void Request::setParams(const void *data) {
    uint8_t length = ActionList::getParamLength(type);
    params.update(data, length);
  }

  const RequestParamSet* Request::getParams() const {
    return &params;
  }
}
