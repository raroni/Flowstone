#ifndef ACTIONS_REQUEST_PARAM_SET_H
#define ACTIONS_REQUEST_PARAM_SET_H

#include "Actions/Config.h"

namespace Actions {
  class RequestParamSet {
  public:
    void update(const void *data, uint8_t length);
  private:
    char data[Config::requestParamSetCapacity];
    uint8_t length = 0;
  };
}

#endif
