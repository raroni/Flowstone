#ifndef WATSON_TRAVERSAL_DIRECTION_H
#define WATSON_TRAVERSAL_DIRECTION_H

#include <stdint.h>

namespace Watson {
  enum class TraversalCommandType : uint8_t {
    Reaction,
    Entry,
    Callback,
    Undefined
  };
}

#endif
