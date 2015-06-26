#include "Actions3/System.h"
#include "Actions3/InstanceStatus.h"
#include "Watson/ServerFunction.h"
#include "Watson/Server.h"
#include "Behavior/BoardKey.h"
#include "Behavior/Server.h"

namespace Behavior {
  namespace Server {
    typedef Watson::Board Board;
    typedef Watson::ResponseBuffer ResponseBuffer;
    typedef Watson::ServerFunction ServerFunction;

    void setupType(BoardKey key, ServerFunction function) {
      uint8_t keyInt = static_cast<uint8_t>(key);
      Watson::Server::configure(keyInt, function);
    }

    void checkThreat(const void *request, const Board *board, ResponseBuffer *response) {
      bool value = false;
      response->set(&value, sizeof(bool));
    }

    void checkWood(const void *request, const Board *board, ResponseBuffer *response) {
      bool value = false;
      response->set(&value, sizeof(bool));
    }

    void getRequestAction(const void *request, const Board *board, ResponseBuffer *response) {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
      Actions3::InstanceHandle actionsHandle = *static_cast<const Actions3::InstanceHandle*>(board->get(keyInt));
      const Actions3::ActionType action = Actions3::System::getRequestActionType(actionsHandle);
      response->set(&action, sizeof(action));
    }

    void getActionStatus(const void *request, const Board *board, ResponseBuffer *response) {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
      Actions3::InstanceHandle actionsHandle = *static_cast<const Actions3::InstanceHandle*>(board->get(keyInt));
      Actions3::InstanceStatus actionStatus = Actions3::System::getStatus(actionsHandle);
      response->set(&actionStatus, sizeof(actionStatus));
    }

    void setup() {
      setupType(BoardKey::IsThreatened, checkThreat);
      setupType(BoardKey::HasWood, checkWood);
      setupType(BoardKey::RequestAction, getRequestAction);
      setupType(BoardKey::ActionStatus, getActionStatus);
    }
  }
}
