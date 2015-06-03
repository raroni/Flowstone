#include "Watson/NodeResult.h"
#include "Behavior/NodeType.h"
#include "Behavior/ThreatCheckNode.h"

namespace Behavior {
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
