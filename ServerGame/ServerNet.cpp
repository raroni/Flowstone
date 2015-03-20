#include <assert.h>
#include "Common/Piper/Config.h"
#include "Common/Piper/Server.h"
#include "ServerGame/ServerGameConfig.h"
#include "ServerGame/ServerGameClientIDPool.h"
#include "ServerGame/ServerAckHelper.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  static ServerGameClientIDPool idPool;
  Piper::Server pipe;

  int8_t indicesByPiperIDs[Piper::Config::Server::clientMax] = { -1 };

  uint8_t indices[ServerGameConfig::clientMax];
  ServerGameClientID ids[ServerGameConfig::clientMax];
  Piper::ClientID piperIDs[ServerGameConfig::clientMax];
  uint8_t sendCounts[ServerGameConfig::clientMax];
  uint8_t count = 0;

  void initialize() {
    ServerAckHelper::initialize();
  }

  void createClient(Piper::ClientID piperID) {
    // todo: better handling, rejection of some kind
    assert(count != ServerGameConfig::clientMax);

    indicesByPiperIDs[piperID] = count;
    ServerGameClientID id = idPool.obtain();
    indices[id] = count;
    ids[count] = id;
    piperIDs[count] = piperID;
    sendCounts[count] = 0;
    count++;
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
      if(indicesByPiperIDs[piperID] == -1) {
        createClient(piperID);
      }
      uint8_t index = indicesByPiperIDs[piperID];
      *id = ids[index];
      ServerAckHelper::handleReceive(*id, *type);
    }

    return result;
  }

  ServerGameClientID getClientID(uint8_t index) {
    return ids[index];
  }

  uint8_t getClientCount() {
    return count;
  }

  uint8_t getSendCount(uint8_t index) {
    return sendCounts[index];
  }

  Piper::Sequence sendMessage(ServerGameClientID clientID, const void *message, uint16_t messageLength) {
    uint8_t index = indices[clientID];
    assert(sendCounts[index] != UINT8_MAX);
    sendCounts[index]++;
    Piper::ClientID piperID = piperIDs[index];
    return pipe.sendMessage(piperID, message, messageLength);
  }

  void dispatch() {
    ServerAckHelper::check();
    pipe.dispatch();
    memset(sendCounts, 0, sizeof(sendCounts));
  }

  void poll() {
    pipe.poll();
  }

  void clear() {
    pipe.clear();
  }
}
