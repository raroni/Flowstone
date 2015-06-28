#include "Actions/TargetReachNode.h"

namespace Actions {
  namespace TargetReachNode {
    void start(NodeCall *call) {
    }

    bool isCompleted(NodeCall *call) {
      return false;
    }

    uint8_t calcConfigLength(const void *args) { return 0; }
    uint8_t calcStateLength(const void *args) { return 0; }
    void configure(const void *args, void *config) { }
  }
}
