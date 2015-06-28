#include <assert.h>
#include <string.h>
#include "Actions/ActionOptionsSet.h"

namespace Actions {
  void ActionOptionsSet::update(const void *data, uint8_t length) {
    assert(length <= capacity);
    memcpy(this->data, data, length);
    this->length = length;
  }

  uint8_t ActionOptionsSet::getLength() const {
    return length;
  }

  const void* ActionOptionsSet::getData() const {
    return data;
  }
}
