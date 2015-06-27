#include "Actions3/Action.h"
#include "Actions3/Request.h"

namespace Actions3 {
  void Request::setOptions(const void *data) {
    uint8_t length = Action::getOptionsLength(type);
    options.update(data, length);
  }

  const void* Request::getOptions() const {
    return options.getData();
  }
}
