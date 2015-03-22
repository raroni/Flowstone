#include <assert.h>
#include "Common/Piper/Server.h"
#include "ServerGame/ServerGameClientSet.h"
#include "ServerGame/ServerAckHelper.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  Piper::Server pipe;

  void initialize() {
    ServerAckHelper::initialize();
  }

  void listen(const Piper::Address &address) {
    pipe.listen(address);
  }

  bool readMessage(ServerGameClientID *id, MessageType *type, const void **message, uint16_t *messageLength) {
    Piper::ClientID piperID;
    bool result = pipe.readMessage(&piperID, message, messageLength);

    if(result) {
      *messageLength = (*messageLength)-1;
      *type = *static_cast<const MessageType*>(*message);
      *message = static_cast<const char*>(*message)+1;

      // todo: handle client overflow
      if(!ServerGameClientSet::locatePiperID(piperID)) {
        ServerGameClientSet::create(piperID);
      }

      *id = ServerGameClientSet::findIDByPiperID(piperID);
      ServerAckHelper::handleReceive(*id, *type);
    }

    return result;
  }

  Piper::Sequence sendMessage(ServerGameClientID clientID, const void *message, uint16_t messageLength) {
    const uint8_t *indices = ServerGameClientSet::indices;
    uint8_t *sendCounts = ServerGameClientSet::sendCounts;
    const Piper::ClientID *piperIDs = ServerGameClientSet::piperIDs;

    uint8_t index = indices[clientID];
    assert(sendCounts[index] != UINT8_MAX);
    sendCounts[index]++;
    Piper::ClientID piperID = piperIDs[index];
    return pipe.sendMessage(piperID, message, messageLength);
  }

  void dispatch() {
    ServerAckHelper::check();
    pipe.dispatch();
    ServerGameClientSet::clearSendCounts();
  }

  void poll() {
    pipe.poll();
  }

  void clear() {
    pipe.clear();
  }
}
