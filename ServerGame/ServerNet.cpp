#include <assert.h>
#include "Common/Piper/Config.h"
#include "Common/Piper/Server.h"
#include "ServerGame/ServerAckHelper.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  static const uint8_t max = 8;
  Piper::Server pipe;
  bool idLookup[Piper::Config::Server::clientMax] = { false };
  uint8_t indices[Piper::Config::Server::clientMax];
  Piper::ClientID ids[max];
  uint8_t sendCounts[max];
  uint8_t count = 0;

  void initialize() {
    ServerAckHelper::initialize();
  }

  void createClient(Piper::ClientID id) {
    // todo: better handling, rejection of some kind
    assert(count != max);

    idLookup[id] = true;
    indices[id] = count;
    ids[count] = id;
    sendCounts[count] = 0;
    count++;
  }

  void listen(const Piper::Address &address) {
    pipe.listen(address);
  }

  bool readMessage(Piper::ClientID *id, MessageType *type, const void **message, uint16_t *messageLength) {
    bool result = pipe.readMessage(id, message, messageLength);

    if(result) {
      *messageLength = (*messageLength)-1;
      *type = *static_cast<const MessageType*>(*message);
      *message = static_cast<const char*>(*message)+1;
      if(!idLookup[*id]) {
        createClient(*id);
      }
      ServerAckHelper::handleReceive(*id, *type);
    }

    return result;
  }

  Piper::ClientID getClientID(uint8_t index) {
    return ids[index];
  }

  uint8_t getClientCount() {
    return count;
  }

  uint8_t getSendCount(uint8_t index) {
    return sendCounts[index];
  }

  Piper::Sequence sendMessage(Piper::ClientID clientID, const void *message, uint16_t messageLength) {
    uint8_t index = indices[clientID];
    assert(sendCounts[index] != UINT8_MAX);
    sendCounts[index]++;
    return pipe.sendMessage(clientID, message, messageLength);
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
