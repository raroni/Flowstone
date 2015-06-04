#include "Watson/NodeType.h"
#include "Watson/NodeResult.h"
#include "Watson/RunDummyNode.h"

namespace Watson {
  namespace RunDummyNode {
    uint8_t structureLength = sizeof(NodeType);
    uint8_t stateLength = 0;

    void enter(TraversalFlow *flow) {
      flow->requestReaction(NodeResult::Running);
    }

    void reset(ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
