#ifndef WATSON_NODE_STACK_H
#define WATSON_NODE_STACK_H

#include "Watson/NodeIndex.h"

namespace Watson {
  class NodeStack {
  public:
    void push(NodeIndex offset);
    NodeIndex pop();
    NodeIndex top() const;
    bool isEmpty() const;
  private:
    static const uint8_t max = 64;
    NodeIndex list[max];
    uint16_t count = 0;
  };
}

#endif
