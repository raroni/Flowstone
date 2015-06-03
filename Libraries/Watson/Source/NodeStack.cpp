#include <assert.h>
#include "Watson/NodeStack.h"

namespace Watson {
  void NodeStack::push(uint16_t offset) {
    assert(max != count);
    list[count++] = offset;
  }

  uint16_t NodeStack::pop() {
    return list[count--];
  }

  uint16_t NodeStack::top() const {
    return list[count-1];
  }

  bool NodeStack::isEmpty() const {
    return count == 0;
  }
}
