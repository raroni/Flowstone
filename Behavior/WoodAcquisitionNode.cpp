#include "Actions3/Request.h"
#include "Actions3/InstanceStatus.h"
#include "Watson/NodeResult.h"
#include "Behavior/BoardKey.h"
#include "Behavior/NodeType.h"
#include "Behavior/WoodAcquisitionNode.h"

namespace Behavior {
  namespace WoodAcquisitionNode {
    typedef Watson::NodeResult NodeResult;
    const uint8_t structureLength = sizeof(NodeType);
    const uint8_t stateLength = 0;

    void enter(Watson::TraversalFlow *flow) {
      BoardKey key;

      key = BoardKey::PendingActionRequest;
      flow->requestBoardData(&key, sizeof(BoardKey));

      key = BoardKey::ActionStatus;
      flow->requestBoardData(&key, sizeof(BoardKey));

      flow->requestCallback(ResponseCallbackIndex);
    }

    void handleResponse(Watson::TraversalFlow *flow) {
      uint8_t keyInt;

      keyInt = static_cast<uint8_t>(BoardKey::PendingActionRequest);
      const Actions3::Request *actionRequest = reinterpret_cast<const Actions3::Request*>(flow->board->get(keyInt));

      keyInt = static_cast<uint8_t>(BoardKey::ActionStatus);
      Actions3::InstanceStatus actionStatus = *reinterpret_cast<const Actions3::InstanceStatus*>(flow->board->get(keyInt));

      if(actionRequest->type == Actions3::ActionType::WoodAcquisition) {
        if(actionStatus == Actions3::InstanceStatus::Completed) {
          flow->requestReaction(NodeResult::Succeeded);
        } else {
          flow->requestReaction(NodeResult::Running);
        }
      } else {
        Actions3::ActionType type = Actions3::ActionType::WoodAcquisition;
        flow->actionStream->write(&type, sizeof(type));
        flow->requestReaction(NodeResult::Running);
      }
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
