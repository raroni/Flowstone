#include "Watson/NodeType.h"
#include "Watson/NodeResult.h"
#include "Watson/FailDummyNode.h"

namespace Watson {
  namespace FailDummyNode {
    uint8_t structureLength = sizeof(NodeType);
    uint8_t stateLength = 0;

    void enter(TraversalFlow *flow) {
      flow->requestReaction(NodeResult::Failed);
    }

    void reset(ResetFlow *flow) { }
    void initializeState(const void *structure, void *state) { }
  }
}
