#ifndef ACTIONS_NODE_INTERFACE_H
#define ACTIONS_NODE_INTERFACE_H

#include "Actions/StartFunction.h"

namespace Actions {
  struct NodeInterface {
    StartFunction start;
  };
}

#endif
