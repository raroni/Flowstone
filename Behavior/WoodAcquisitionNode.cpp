#include "Actions/Request.h"
#include "Actions/InstanceStatus.h"
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
      const Actions::Request *actionRequest = reinterpret_cast<const Actions::Request*>(flow->board->get(keyInt));

      keyInt = static_cast<uint8_t>(BoardKey::ActionStatus);
      Actions::InstanceStatus actionStatus = *reinterpret_cast<const Actions::InstanceStatus*>(flow->board->get(keyInt));

      if(actionRequest->type == Actions::ActionType::WoodAcquisition) {
        if(actionStatus == Actions::InstanceStatus::Completed) {
          flow->requestReaction(NodeResult::Succeeded);
        } else {
          flow->requestReaction(NodeResult::Running);
        }
      } else {
        Actions::ActionType type = Actions::ActionType::WoodAcquisition;
        flow->actionStream->write(&type, sizeof(type));
        flow->requestReaction(NodeResult::Running);
      }
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
