#include <assert.h>
#include "Actions/Action.h"
#include "Actions/Request.h"

namespace Actions {
  void Request::setParams(const void *data) {
    uint8_t length = Action::getParamLength(type);
    params.update(data, length);
  }

  const RequestParamSet* Request::getParams() const {
    return &params;
  }
}
