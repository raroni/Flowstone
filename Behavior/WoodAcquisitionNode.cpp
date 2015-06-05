#include "Actions/Status.h"
#include "Actions/Request.h"
#include "Actions/Type.h"
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

      if(actionRequest->type == Actions::Type::WoodAcquisition) {
        if(actionStatus == Actions::Status::Completed) {
          flow->requestReaction(NodeResult::Succeeded);
        } else {
          flow->requestReaction(NodeResult::Running);
        }
      } else {
        Actions::Type request = Actions::Type::WoodAcquisition;
        flow->actionStream->write(&request, sizeof(request));
        flow->requestReaction(NodeResult::Running);
      }
    }

    void reset(Watson::ResetFlow *flow) { }

    void initializeState(const void *structure, void *state) { }
  }
}
