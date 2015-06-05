#include <assert.h>
#include <string.h>
#include "Actions/RequestParamSet.h"

namespace Actions {
  void RequestParamSet::update(const void *data, uint8_t length) {
    assert(length <= Config::requestParamSetCapacity);
    memcpy(this->data, data, length);
    this->length = length;
  }
}
