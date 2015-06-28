#include "Actions/System.h"
#include "Actions/InstanceStatus.h"
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

    void getPendingActionRequest(const void *request, const Board *board, ResponseBuffer *response) {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
      Actions::InstanceHandle actionsHandle = *static_cast<const Actions::InstanceHandle*>(board->get(keyInt));
      const Actions::Request *actionRequest = Actions::System::getPendingRequest(actionsHandle);
      response->set(actionRequest, sizeof(*actionRequest));
    }

    void getActionStatus(const void *request, const Board *board, ResponseBuffer *response) {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
      Actions::InstanceHandle actionsHandle = *static_cast<const Actions::InstanceHandle*>(board->get(keyInt));
      Actions::InstanceStatus actionStatus = Actions::System::getStatus(actionsHandle);
      response->set(&actionStatus, sizeof(actionStatus));
    }

    void setup() {
      setupType(BoardKey::IsThreatened, checkThreat);
      setupType(BoardKey::HasWood, checkWood);
      setupType(BoardKey::PendingActionRequest, getPendingActionRequest);
      setupType(BoardKey::ActionStatus, getActionStatus);
    }
  }
}
