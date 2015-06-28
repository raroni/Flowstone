#include "Actions/Action.h"
#include "Actions/Request.h"

namespace Actions {
  void Request::setOptions(const void *data) {
    uint8_t length = Action::getOptionsLength(type);
    options.update(data, length);
  }

  const void* Request::getOptions() const {
    return options.getData();
  }
}
