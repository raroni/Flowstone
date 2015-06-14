#include "Actions/TreeChopNode.h"

namespace Actions {
  namespace TreeChopNode {
    void start(NodeFlow *flow) {
    }

    bool isCompleted(NodeFlow *flow) {
      return false;
    }

    uint8_t calcConfigLength(const void *args) { return 0; }
    uint8_t calcStateLength(const void *args) { return 0; }
    void configure(const void *args, void *config) { }
  }
}
