#include "Watson/NodeResult.h"
#include "AI/NodeType.h"
#include "AI/ThreatCheckNode.h"

namespace AI {
  namespace ThreatCheckNode {
    typedef Watson::NodeResult NodeResult;
    const uint8_t structureLength = sizeof(NodeType);
    const uint8_t stateLength = 0;

    void enter(Watson::TraversalFlow *flow) {
      flow->requestReaction(NodeResult::Failed);
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
