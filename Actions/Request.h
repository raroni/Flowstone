#ifndef ACTIONS_REQUEST_H
#define ACTIONS_REQUEST_H

#include "Actions/ActionOptionsSet.h"
#include "Actions/ActionType.h"

namespace Actions {
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
