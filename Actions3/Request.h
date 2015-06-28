#ifndef ACTIONS3_REQUEST_H
#define ACTIONS3_REQUEST_H

#include "Actions3/ActionOptionsSet.h"
#include "Actions3/ActionType.h"

namespace Actions3 {
  class Request {
  public:
    ActionType type;
    void setOptions(const void *data);
    const void* getOptions() const;
  private:
    ActionOptionsSet options;
  };
}

#endif
