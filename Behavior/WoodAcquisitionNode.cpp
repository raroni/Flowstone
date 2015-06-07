#include "Actions/Status.h"
#include "Actions/Request.h"
#include "Actions/ActionTypes.h"
#include "Actions/ActionTypeIndex.h"
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

      key = BoardKey::ActionRequest;
      flow->requestBoardData(&key, sizeof(BoardKey));

      key = BoardKey::ActionStatus;
      flow->requestBoardData(&key, sizeof(BoardKey));

      flow->requestCallback(ResponseCallbackIndex);
    }

    void handleResponse(Watson::TraversalFlow *flow) {
      uint8_t keyInt;

      keyInt = static_cast<uint8_t>(BoardKey::ActionRequest);
      const Actions::Request *actionRequest = reinterpret_cast<const Actions::Request*>(flow->board->get(keyInt));

      keyInt = static_cast<uint8_t>(BoardKey::ActionStatus);
      Actions::Status actionStatus = *reinterpret_cast<const Actions::Status*>(flow->board->get(keyInt));

      if(actionRequest->type == Actions::ActionTypes::woodAcquisition) {
        if(actionStatus == Actions::Status::Completed) {
          flow->requestReaction(NodeResult::Succeeded);
        } else {
          flow->requestReaction(NodeResult::Running);
        }
      } else {
        Actions::ActionTypeIndex type = Actions::ActionTypes::woodAcquisition;
        flow->actionStream->write(&type, sizeof(type));
        flow->requestReaction(NodeResult::Running);
      }
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
