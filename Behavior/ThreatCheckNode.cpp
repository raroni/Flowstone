#include "Watson/NodeResult.h"
#include "Behavior/BoardKey.h"
#include "Behavior/NodeType.h"
#include "Behavior/ThreatCheckNode.h"

namespace Behavior {
  namespace ThreatCheckNode {
    typedef Watson::NodeResult NodeResult;
    const uint8_t structureLength = sizeof(NodeType);
    const uint8_t stateLength = 0;

    void enter(Watson::TraversalFlow *flow) {
      BoardKey key = BoardKey::IsThreatened;
      flow->requestBoardData(&key, sizeof(BoardKey));
      flow->requestCallback(ResponseCallbackIndex);
    }

    void handleResponse(Watson::TraversalFlow *flow) {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::IsThreatened);
      bool isThreatened = *reinterpret_cast<const bool*>(flow->board->get(keyInt));
      if(isThreatened) {
        flow->requestReaction(NodeResult::Succeeded);
      } else {
        flow->requestReaction(NodeResult::Failed);
      }
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
