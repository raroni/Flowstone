#ifndef ACTIONS_REQUEST_H
#define ACTIONS_REQUEST_H

#include "Actions/RequestParamSet.h"
#include "Actions/Type.h"

namespace Actions {
  class Request {
  public:
    Type type;
    void setParams(const void *data);
    const RequestParamSet* getParams() const;
  private:
    RequestParamSet params;
  };
}

#endif
