#ifndef WATSON_RESET_FLOW_H
#define WATSON_RESET_FLOW_H

#include "Watson/NodeStack.h"

namespace Watson {
  class ResetFlow {
  public:
    ResetFlow(NodeStack *stack);
    void push(NodeIndex node);
    const void *structure = nullptr;
    void *state = nullptr;
  private:
    NodeStack *stack = nullptr;
  };
}

#endif
