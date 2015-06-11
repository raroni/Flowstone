#include <assert.h>
#include "Actions/ActionTypeList.h"
#include "Actions/Request.h"

namespace Actions {
  void Request::setParams(const void *data) {
    uint8_t length = ActionTypeList::getParamLength(type);
    params.update(data, length);
  }

  const RequestParamSet* Request::getParams() const {
    return &params;
  }
}
