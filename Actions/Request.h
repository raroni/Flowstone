#ifndef ACTIONS_REQUEST_H
#define ACTIONS_REQUEST_H

#include "Actions/RequestParamSet.h"
#include "Actions/Type.h"

namespace Actions {
  class Request {
    Type type;
    void setParams(const void *data, uint8_t length);
    const RequestParamSet* getParams() const;
  private:
    RequestParamSet params;
  };
}

#endif
