#include "Watson/ResetFlow.h"

namespace Watson {
  ResetFlow::ResetFlow(NodeStack *stack) : stack(stack) { }

  void ResetFlow::push(NodeIndex node) {
    stack->push(node);
  }
}
